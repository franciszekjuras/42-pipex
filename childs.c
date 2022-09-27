/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:03:37 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 17:49:05 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <libft/libft.h>
#include "childs.h"

static int	get_retval_from_exit_status(int exit_status)
{
	if (!WIFSIGNALED(exit_status))
		return (WEXITSTATUS(exit_status));
	else
		return (128 + WTERMSIG(exit_status));
}

void	childs_init(t_childs *childs)
{
	childs->number = 0;
	childs->last = -1;
}

void	childs_update(t_childs *childs, pid_t child)
{
	if (child >= 0)
		childs->number++;
	childs->last = child;
}

int	childs_wait_until_all_exit(t_childs *childs)
{
	int		i;
	int		retval;
	int		exited_status;
	pid_t	exited_pid;

	retval = 0;
	i = 0;
	while (i < childs->number)
	{
		exited_pid = wait(&exited_status);
		if (exited_pid == childs->last && childs->last >= 0)
			retval = get_retval_from_exit_status(exited_status);
		++i;
	}
	if (childs->last < 0)
		retval = 127;
	return (retval);
}
