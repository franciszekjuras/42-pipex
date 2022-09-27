/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:32:23 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 13:00:51 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include "app.h"
#include "childs.h"

int	main(int argc, char **argv)
{
	t_app	app;
	int		file_in;
	int		file_out;
	int		pipe_fds[2];

	if (argc != 5)
		return (EINVAL);
	app_init(&app, argv[0]);
	if (app_pipe(&app, pipe_fds) < 0)
		return (app_free(&app));
	file_in = app_open(&app, argv[1], O_RDONLY);
	file_out = app_open(&app, argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	childs_update(&app.childs,
		app_exec(&app, argv[2], file_in, pipe_fds[1]));
	childs_update(&app.childs,
		app_exec(&app, argv[3], pipe_fds[0], file_out));
	app_free(&app);
	return (childs_wait_until_all_exit(&app.childs));
}
