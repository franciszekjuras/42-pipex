/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:32:23 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/25 19:47:19 by fjuras           ###   ########.fr       */
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

void	childs_info_update(t_childs_info *childs, pid_t child)
{
	if (child >= 0)
		childs->number++;
	childs->last = child;
}

pid_t	execute_clean_up(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
	return (-1);
}

pid_t	execute_with_custom_io(char *my_name, char *cmd, int fd_in, int fd_out)
{
	char	**args;
	char	*prog;
	pid_t	child;

	if (fd_in < 0 || fd_out < 0)
		return (execute_clean_up(fd_in, fd_out));
	args = ft_split(cmd, ' ');
	prog = args[0];
	child = fork();
	if (child == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execve(prog, args, environ);
		ft_dprintf(2, "%s: %s: %s\n", my_name, prog, strerror(errno));
		exit(errno);
	}
	ft_freeparr((void **)args);
	close(fd_in);
	close(fd_out);
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

int	open_with_error_print(char *my_name, char *file, int flags)
{
	int	fd;

	if (flags == O_RDONLY)
		fd = open(file, flags);
	else
		fd = open(file, flags, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: %s\n", my_name, file, strerror(errno));
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	t_childs_info	childs;
	int				file_in;
	int				file_out;
	int				pipe_fds[2];

	(void) argc;
	childs_info_init(&childs);
	pipe(pipe_fds);
	file_in = open_with_error_print(argv[0], argv[1], O_RDONLY);
	file_out = open_with_error_print(
			argv[0], argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	childs_info_update(
		&childs, execute_with_custom_io(argv[0], argv[2], file_in, pipe_fds[1]));
	childs_info_update(
		&childs, execute_with_custom_io(argv[0], argv[3], pipe_fds[0], file_out));
	return (wait_until_all_childs_exit(childs));
}
