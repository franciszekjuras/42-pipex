/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:47:42 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 13:01:25 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include <sys/types.h>
# include "childs.h"

typedef struct s_app
{
	char		*name;
	char		**path;
	t_childs	childs;
}	t_app;

void	app_init(t_app *app, char *name);
int		app_free(t_app *app);
int		app_pipe(t_app *app, int pipe_fds[2]);
int		app_open(t_app *app, char *file, int flags);
pid_t	app_exec(t_app *app, char *cmd, int fd_in, int fd_out);

#endif
