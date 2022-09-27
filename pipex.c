/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:32:23 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/26 21:41:28 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libft/libft.h>

extern char	**environ;

typedef struct s_childs_info
{
	int		number;
	pid_t	last;
}	t_childs_info;

void	childs_info_init(t_childs_info *childs)
{
	childs->number = 0;
	childs->last = -1;
}

typedef struct s_app_ctx
{
	char			*name;
	char			**path;
	t_childs_info	childs;
}	t_app_ctx;

void	childs_info_update(t_childs_info *childs, pid_t child)
{
	if (child >= 0)
		childs->number++;
	childs->last = child;
}

char	**extract_path_arr_from_env(void)
{
	int	i;

	i = 0;
	while (environ[i] != NULL && ft_strncmp(environ[i], "PATH=", 5) != 0)
		++i;
	if (environ[i] == NULL)
		return (ft_split("", ':'));
	else
		return (ft_split(environ[i] + 5, ':'));
}

int	check_if_path_is_executable(char *path, char *prog, char **candidate)
{
	char	*full_path;
	int		is_executable;

	is_executable = 0;
	full_path = ft_pathjoin(path, prog);
	if (access(full_path, F_OK) == 0)
	{
		free(*candidate);
		*candidate = ft_strdup(full_path);
		if (access(full_path, X_OK) == 0)
			is_executable = 1;
	}
	free(full_path);
	return (is_executable);
}

char	*resolve_prog_path(t_app_ctx *app_ctx, char *prog)
{
	char	*candidate;
	char	**path;

	if (prog == NULL)
		return (NULL);
	if (ft_strchr(prog, '/') != NULL)
		return (ft_strdup(prog));
	candidate = NULL;
	path = app_ctx->path;
	while (*path != NULL)
	{
		if (check_if_path_is_executable(*path, prog, &candidate))
			break ;
		++path;
	}
	if (candidate == NULL)
		ft_dprintf(2, "%s: %s: %s\n", app_ctx->name, prog, "command not found");
	return (candidate);
}

pid_t	execute_clean_up(char **args, int fd_in, int fd_out)
{
	if (args != NULL)
		ft_freeparr((void **)args);
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
	return (-1);
}

pid_t	exec_with_io_fds(t_app_ctx *app_ctx, char *cmd, int fd_in, int fd_out)
{
	char	*prog_path;
	char	**args;
	pid_t	child;

	if (fd_in < 0 || fd_out < 0)
		return (execute_clean_up(NULL, fd_in, fd_out));
	args = ft_split(cmd, ' ');
	prog_path = resolve_prog_path(app_ctx, args[0]);
	if (prog_path == NULL)
		return (execute_clean_up(args, fd_in, fd_out));
	child = fork();
	if (child == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execve(prog_path, args, environ);
		ft_dprintf(2, "%s: %s: %s\n", app_ctx->name, args[0], strerror(errno));
		exit(errno);
	}
	free(prog_path);
	(void)(execute_clean_up(args, fd_in, fd_out));
	return (child);
}

int	get_retval_from_exit_status(int exit_status)
{
	if (!WIFSIGNALED(exit_status))
		return (WEXITSTATUS(exit_status));
	else
		return (128 + WTERMSIG(exit_status));
}

int	wait_until_all_childs_exit(t_childs_info childs)
{
	int		i;
	int		retval;
	int		exited_status;
	pid_t	exited_pid;

	retval = 0;
	i = 0;
	while (i < childs.number)
	{
		exited_pid = wait(&exited_status);
		if (exited_pid == childs.last && childs.last >= 0)
			retval = get_retval_from_exit_status(exited_status);
		++i;
	}
	if (childs.last < 0)
		retval = errno;
	return (retval);
}

int	open_with_error_print(t_app_ctx *app_ctx, char *file, int flags)
{
	int	fd;

	if (flags == O_RDONLY)
		fd = open(file, flags);
	else
		fd = open(file, flags, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: %s\n", app_ctx->name, file, strerror(errno));
	}
	return (fd);
}

void	app_ctx_init(t_app_ctx *app_ctx, char *name)
{
	app_ctx->name = ft_strdup(name);
	app_ctx->path = extract_path_arr_from_env();
	childs_info_init(&app_ctx->childs);
}

void	app_ctx_free(t_app_ctx *app_ctx)
{
	free(app_ctx->name);
	ft_freeparr((void **)app_ctx->path);
}

int	main(int argc, char **argv)
{
	t_app_ctx		app_ctx;
	int				file_in;
	int				file_out;
	int				pipe_fds[2];

	if (argc != 5)
		return (EINVAL);
	app_ctx_init(&app_ctx, argv[0]);
	pipe(pipe_fds);
	file_in = open_with_error_print(&app_ctx, argv[1], O_RDONLY);
	file_out = open_with_error_print(
			&app_ctx, argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	childs_info_update(&app_ctx.childs,
		exec_with_io_fds(&app_ctx, argv[2], file_in, pipe_fds[1]));
	childs_info_update(&app_ctx.childs,
		exec_with_io_fds(&app_ctx, argv[3], pipe_fds[0], file_out));
	app_ctx_free(&app_ctx);
	return (wait_until_all_childs_exit(app_ctx.childs));
}
