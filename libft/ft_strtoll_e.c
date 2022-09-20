/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 23:03:34 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/19 16:27:39 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static void	ft_strtoll_get_limits(
	long long limit, long long *lim_dv_base, int *lim_md_base, int base)
{
	*lim_dv_base = limit;
	*lim_md_base = (*lim_dv_base) % base;
	*lim_dv_base /= base;
	if (limit < 0)
	{
		if (*lim_md_base > 0)
		{
			*lim_md_base -= base;
			*lim_dv_base += 1;
		}
		*lim_md_base *= -1;
	}
}

static unsigned long long	ft_strtoll_raw_pos_e_(
	const char *np, char **ep, int base, int *err)
{
	long long	max_dv_base;
	int			max_md_base;
	int			c;
	long long	r;

	r = 0;
	ft_strtoll_get_limits(LLONG_MAX, &max_dv_base, &max_md_base, base);
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
		r = LLONG_MAX;
	}
	while (c >= 0)
		c = ft_chartonum_base(*np++, base);
	*ep = (char *)(np - 1);
	return (r);
}

static long long	ft_strtoll_raw_neg_e_(
	const char *np, char **ep, int base, int *err)
{
	long long	min_dv_base;
	int			min_md_base;
	int			c;
	long long	r;

	r = 0;
	ft_strtoll_get_limits(LLONG_MIN, &min_dv_base, &min_md_base, base);
	while (1)
	{
		c = ft_chartonum_base(*np++, base);
		if (c < 0 || r < min_dv_base || (r == min_dv_base && c > min_md_base))
			break ;
		r *= base;
		r -= c;
	}
	if (c >= 0)
	{
		*err |= FT_STRTOI_OVERFLOW;
		r = LLONG_MIN;
	}
	while (c >= 0)
		c = ft_chartonum_base(*np++, base);
	*ep = (char *)(np - 1);
	return (r);
}

long long	ft_strtoll_e(const char *np, char **ep, int base, int *err)
{
	long long			r;
	int					s;

	*err = 0;
	s = ft_strtoi_parse_prefix_e((char **) &np, &base, err);
	r = 0;
	if (!(*err))
	{
		if (s > 0)
			r = ft_strtoll_raw_pos_e_(np, (char **) &np, base, err);
		else
			r = ft_strtoll_raw_neg_e_(np, (char **) &np, base, err);
	}
	if (ep != 0)
		*ep = (char *) np;
	return (r);
}
