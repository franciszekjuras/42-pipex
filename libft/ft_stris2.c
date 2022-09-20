/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stris2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:52:23 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/12 18:26:47 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c < 127);
}

int	ft_isascii(int c)
{
	return (c >= 0 && c < 128);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == '\f');
}

int	ft_isinset(int c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_idxinset(int c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (i);
		i++;
	}
	return (-1);
}
