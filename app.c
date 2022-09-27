/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:54:11 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 12:54:17 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <libft/libft.h>
#include "app_utils.h"
#include "app.h"

extern char	**environ;

void	app_init(t_app *app, char *name)
{
	app->name = ft_strdup(name);
	app->path = extract_path_arr_from_env();
	childs_init(&app->childs);
}

int	app_free(t_app *app)
{
	free(app->name);
	ft_freeparr((void **)app->path);
	return (0);
}

int	app_pipe(t_app *app, int pipe_fds[2])
{
	if (pipe(pipe_fds) == 0)
		return (0);
	else
	{
		ft_dprintf(2, "%s: %s\n", app->name, strerror(errno));
		return (-1);
	}
}

int	app_open(t_app *app, char *file, int flags)
{
	int	fd;

	if (flags == O_RDONLY)
		fd = open(file, flags);
	else
		fd = open(file, flags, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: %s\n", app->name, file, strerror(errno));
	}
	return (fd);
}

pid_t	app_exec(t_app *app, char *cmd, int fd_in, int fd_out)
{
	char	*prog_path;
	char	**args;
	pid_t	child;

	if (fd_in < 0 || fd_out < 0)
		return (exec_clean_up(NULL, fd_in, fd_out));
	args = ft_split(cmd, ' ');
	prog_path = resolve_prog_path(app, args[0]);
	if (prog_path == NULL)
		return (exec_clean_up(args, fd_in, fd_out));
	child = fork();
	if (child == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execve(prog_path, args, environ);
		ft_dprintf(2, "%s: %s: %s\n", app->name, args[0], strerror(errno));
		exit(errno);
	}
	free(prog_path);
	(void)(exec_clean_up(args, fd_in, fd_out));
	return (child);
}
