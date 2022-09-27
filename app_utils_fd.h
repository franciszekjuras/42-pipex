/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_utils_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:21:08 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 17:16:24 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_UTILS_FD_H
# define APP_UTILS_FD_H

# include "app.h"

void	app_track_fd(t_app *app, int fd);
void	app_close_tracked_fds(t_app *app);

#endif
