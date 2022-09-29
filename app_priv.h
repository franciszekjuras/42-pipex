/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_priv.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:21:08 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/29 18:40:34 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_PRIV_H
# define APP_PRIV_H

# include <sys/types.h>
# include "exec_data.h"
# include "app.h"

void	app_track_fd(t_app *app, int fd);
void	app_close_tracked_fds(t_app *app);
char	*app_resolve_prog_path(t_app *app, char *prog);
void	app_exec_child_side(t_app *app, t_exec_data *exec_data);

#endif
