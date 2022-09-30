/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_priv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:22:54 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/30 12:25:56 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libft/libft.h>
#include "app.h"
#include "exec_data.h"
#include "utils.h"

extern char	**environ;

void	app_track_fd(t_app *app, int fd)
{
	if (fd >= 0)
		app->fds[app->fds_end++] = fd;
}

void	app_close_tracked_fds(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->fds_end)
		close(app->fds[i++]);
	app->fds_end = 0;
}

char	*app_resolve_prog_path(t_app *app, char *prog)
{
	char	*candidate;
	char	**path;

	if (prog == NULL)
		return (NULL);
	if (ft_strchr(prog, '/') != NULL)
		return (ft_strdup(prog));
	candidate = NULL;
	path = app->path;
	while (*path != NULL)
	{
		if (check_if_path_is_executable(*path, prog, &candidate))
			break ;
		++path;
	}
	if (candidate == NULL)
		ft_dprintf(2, "%s: %s: %s\n", app->name, prog, "command not found");
	return (candidate);
}

void	app_exec_child_side(t_app *app, t_exec_data *exec_data)
{
	dup2(exec_data->fd_in, STDIN_FILENO);
	dup2(exec_data->fd_out, STDOUT_FILENO);
	app_close_tracked_fds(app);
	execve(exec_data->prog_path, exec_data->args, environ);
	ft_dprintf(2, "%s: %s: %s\n", app->name,
		exec_data->args[0], strerror(errno));
	(void)(exec_data_clean_up(exec_data));
	app_free(app);
	exit(errno);
}
