/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:33:57 by fjuras            #+#    #+#             */
/*   Updated: 2022/04/05 21:35:40 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_absu(int n)
{
	if (n < 0)
		return (((unsigned int) -(n + 1)) + 1u);
	return ((unsigned int) n);
}

unsigned long long	ft_absull(long long n)
{
	if (n < 0)
		return (((unsigned long long) -(n + 1)) + 1ull);
	return ((unsigned long long) n);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	ft_max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

int	ft_min(int n1, int n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}
