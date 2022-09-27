/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:04:13 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 18:15:25 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_DATA_H
# define EXEC_DATA_H

# include <sys/types.h>
# include "app.h"

typedef struct s_exec_data
{
	char	*prog_path;
	char	**args;
	int		fd_in;
	int		fd_out;
}	t_exec_data;

void	exec_data_init(t_exec_data *exec_data, int fd_in, int fd_out);
pid_t	exec_data_clean_up(t_exec_data *exec_data);

#endif