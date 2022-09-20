/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtofp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:20:00 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/22 10:38:28 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculate position of first non-zero digit relative to decimal point
 * e.g. for 0.1 position is 0, for 42.21 it's 2, for 0.03 it's -1
 * 
 * @param np converted string
 * @param pos pointer to store postion
 * @return char* pointer to end of number
 */
static char	*ft_strtofp_preparse(char *np, int *pos)
{
	int	i;
	int	mark;

	i = 0;
	while (np[i] == '0')
		++i;
	mark = i;
	if (np[i] == '.')
	{
		++i;
		while (np[i] == '0')
			++i;
		*pos = mark - i + 1;
	}
	else
	{
		while (ft_isdigit(np[i]))
			++i;
		*pos = i - mark;
		if (np[i] == '.')
			++i;
	}
	while (ft_isdigit(np[i]))
		++i;
	return (np + i);
}

static long long	ft_strtofp_base(char *np, char *end, int *digits)
{
	long long	res;
	int			dig;

	while (*np == '0' || *np == '.')
		++np;
	res = 0;
	dig = 0;
	while (dig < 18 && np < end && ft_isdigit(*np))
	{
		res *= 10;
		res += *np - '0';
		++dig;
		++np;
		if (*np == '.')
			++np;
	}
	*digits = dig;
	return (res);
}

char	*ft_strtofp(char *np, long long *base, int *pow10, int *err)
{
	int		neg;
	char	*end;
	int		pos;
	int		digits;

	*err = 0;
	neg = 0;
	while (ft_isspace(*np))
		++np;
	if (*np == '-')
	{
		neg = 1;
		++np;
	}
	else if (*np == '+')
		++np;
	end = ft_strtofp_preparse(np, &pos);
	if (end == np || (end == np + 1 && *np == '.'))
		*err |= FT_STRTOI_EMPTY;
	*base = ft_strtofp_base(np, end, &digits);
	if (neg)
		*base = -*base;
	*pow10 = (pos - digits);
	return (end);
}
