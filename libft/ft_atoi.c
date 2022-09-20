/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:07:34 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/16 13:44:18 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_ll(const char *np, int i, int s, int base)
{
	int	r;

	i--;
	r = 0;
	while (i >= 0)
	{
		r += s * (np[i] - '0');
		s *= base;
		i--;
	}
	return (r);
}

int	ft_atoi(const char *np)
{
	int	s;
	int	i;

	while (ft_isspace(*np))
		np++;
	s = 1;
	if (*np == '-')
		s = -1;
	if (*np == '-' || *np == '+')
		np++;
	i = 0;
	while (ft_isdigit(np[i]))
		i++;
	return (ft_atoi_ll(np, i, s, 10));
}
