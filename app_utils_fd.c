/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_utils_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:21:08 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 17:36:25 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "app.h"

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
