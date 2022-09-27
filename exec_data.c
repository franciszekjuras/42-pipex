/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:04:13 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 18:15:14 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <libft/libft.h>
#include "exec_data.h"

void	exec_data_init(t_exec_data *exec_data, int fd_in, int fd_out)
{
	exec_data->prog_path = NULL;
	exec_data->args = NULL;
	exec_data->fd_in = fd_in;
	exec_data->fd_out = fd_out;
}

pid_t	exec_data_clean_up(t_exec_data *exec_data)
{
	if (exec_data->prog_path != NULL)
		free(exec_data->prog_path);
	if (exec_data->args != NULL)
		ft_freeparr((void **)exec_data->args);
	if (exec_data->fd_in >= 0)
		close(exec_data->fd_in);
	if (exec_data->fd_out >= 0)
		close(exec_data->fd_out);
	return (-1);
}
