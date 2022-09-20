/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtonum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 23:03:34 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/22 10:34:58 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_strtonum(
				char **npp, long long min, long long max, int *err)
{
	long long	r;

	*err = 0;
	r = ft_strtoll_e(*npp, npp, 10, err);
	if (r < min)
	{
		r = min;
		*err |= FT_STRTOI_OVERFLOW;
	}
	else if (r > max)
	{
		r = max;
		*err |= FT_STRTOI_OVERFLOW;
	}
	return (r);
}
