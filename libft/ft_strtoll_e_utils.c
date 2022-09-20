/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll_e_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:47:47 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/16 14:17:54 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_chartonum_base(char c, int base)
{
	int	r;

	r = c;
	if (ft_isdigit(r))
		r -= '0';
	else if (ft_islower(r))
		r -= (int) 'a' - 10;
	else if (ft_isupper(r))
		r -= (int) 'A' - 10;
	else
		r = -1;
	if (r < 0 || r >= base)
		return (-1);
	return (r);
}

int	ft_strtoi_parse_prefix_e(char **npp, int *base, int *err)
{
	const char	*np;
	int			sign;

	np = *npp;
	while (ft_isspace(*np))
		np++;
	sign = 1;
	if (*np == '-')
		sign = -1;
	if (*np == '-' || *np == '+')
		np++;
	*npp = (char *) np;
	if (*base < 2 || *base > 36)
		*err |= FT_STRTOI_BASE;
	else if (ft_chartonum_base(*np, *base) < 0)
		*err |= FT_STRTOI_EMPTY;
	return (sign);
}
