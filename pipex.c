/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:32:23 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/19 14:51:48 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>

int	main(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_dprintf(2, "%s: number of arguments is not 4", argv[0]);
		return -1;
	}
	return 0;
}
