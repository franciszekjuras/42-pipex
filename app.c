/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:54:11 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 18:20:09 by fjuras           ###   ########.fr       */
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
#include "app_utils_fd.h"
#include "exec_data.h"
#include "app.h"

void	app_init(t_app *app, char *name)
{
	app->name = ft_strdup(name);
	app->path = extract_path_arr_from_env();
	app->fds_end = 0;
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
	{
		app_track_fd(app, pipe_fds[0]);
		app_track_fd(app, pipe_fds[1]);
		return (0);
	}
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
	app_track_fd(app, fd);
	return (fd);
}

pid_t	app_exec(t_app *app, char *cmd, int fd_in, int fd_out)
{
	t_exec_data	exec_data;
	pid_t		child;

	exec_data_init(&exec_data, fd_in, fd_out);
	if (fd_in < 0 || fd_out < 0)
		return (exec_data_clean_up(&exec_data));
	exec_data.args = ft_split(cmd, ' ');
	exec_data.prog_path = resolve_prog_path(app, exec_data.args[0]);
	if (exec_data.prog_path == NULL)
		return (exec_data_clean_up(&exec_data));
	child = fork();
	if (child == 0)
		app_exec_child_side(app, &exec_data);
	(void)(exec_data_clean_up(&exec_data));
	return (child);
}
