/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoull_e.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 23:03:34 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/19 16:28:06 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static void	ft_strtoll_get_limits(
	unsigned long long limit, unsigned long long *lim_dv_base,
	int *lim_md_base, int base)
{
	*lim_dv_base = limit;
	*lim_md_base = (*lim_dv_base) % base;
	*lim_dv_base /= base;
}

static unsigned long long	ft_strtoull_raw_e_(
	const char *np, char **ep, int base, int *err)
{
	unsigned long long	max_dv_base;
	int					max_md_base;
	int					c;
	unsigned long long	r;

	r = 0;
	ft_strtoll_get_limits(ULLONG_MAX, &max_dv_base, &max_md_base, base);
	while (1)
	{
		c = ft_chartonum_base(*np++, base);
		if (c < 0 || r > max_dv_base || (r == max_dv_base && c > max_md_base))
			break ;
		r *= base;
		r += c;
	}
	if (c >= 0)
	{
		*err |= FT_STRTOI_OVERFLOW;
		r = ULLONG_MAX;
	}
	while (c >= 0)
		c = ft_chartonum_base(*np++, base);
	*ep = (char *)(np - 1);
	return (r);
}

unsigned long long	ft_strtoull_e(
	const char *np, char **ep, int base, int *err)
{
	unsigned long long	r;
	int					s;

	*err = 0;
	s = ft_strtoi_parse_prefix_e((char **) &np, &base, err);
	r = 0;
	if (!(*err))
	{
		r = ft_strtoull_raw_e_(np, (char **) &np, base, err);
		if (s < 0 && r != 0)
		{
			r = 0;
			*err |= FT_STRTOI_OVERFLOW;
		}
	}
	if (ep != 0)
		*ep = (char *) np;
	return (r);
}
