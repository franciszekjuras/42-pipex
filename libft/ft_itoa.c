/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:07:34 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/16 14:22:05 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_numtochar(int n)
{
	if (n < 0 || n > 36)
		return ('#');
	if (n <= 9)
		return ('0' + n);
	return ('a' + (n - 10));
}

char	*ft_itoa(int n)
{
	char			buf[20];
	unsigned int	un;
	int				i;

	un = ft_absu(n);
	i = 20 - 1;
	buf[i--] = 0;
	while (un != 0)
	{
		buf[i--] = '0' + un % 10;
		un /= 10;
	}
	if (n == 0)
		buf[i--] = '0';
	else if (n < 0)
		buf[i--] = '-';
	i++;
	return (ft_strdup(buf + i));
}

char	*ft_lltoa_base_buf(long long n, int base, char *buf, int size)
{
	unsigned long long	un;
	char				*pos;

	un = ft_absull(n);
	pos = ft_ulltoa_base_buf(un, base, buf, size);
	if (pos > buf && n < 0)
		*(--pos) = '-';
	return (pos);
}

char	*ft_ulltoa_base_buf(unsigned long long n, int base, char *buf, int size)
{
	char	*pos;

	pos = buf + size - 1;
	*(--pos) = '\0';
	if (n == 0)
		*(--pos) = '0';
	while (n != 0 && pos >= buf)
	{
		*(--pos) = ft_numtochar(n % base);
		n /= base;
	}
	return (pos);
}
