/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:22:54 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 18:23:05 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <libft/libft.h>
#include "app.h"
#include "app_utils.h"
#include "app_utils_fd.h"
#include "exec_data.h"

extern char	**environ;

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

char	*resolve_prog_path(t_app *app, char *prog)
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
