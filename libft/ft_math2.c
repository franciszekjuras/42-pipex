/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:33:57 by fjuras            #+#    #+#             */
/*   Updated: 2022/04/19 09:54:17 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_fmax(double n1, double n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

double	ft_fmin(double n1, double n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}
