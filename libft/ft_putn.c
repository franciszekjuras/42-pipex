/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:44:58 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/15 16:17:20 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putcharn_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putncharn_fd(char c, int n, int fd)
{
	char	buffer[64];
	int		total;
	int		r;

	total = 0;
	ft_memset(buffer, c, ft_min(64, n));
	while (n > 0)
	{
		r = write(fd, buffer, ft_min(64, n));
		n -= 64;
		if (r < 0)
			return (-1);
		total += r;
	}
	return (total);
}

int	ft_putstrn_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	return (write(fd, s, len));
}

int	ft_putendln_fd(char *s, int fd)
{
	int	r1;
	int	r2;

	r1 = ft_putstrn_fd(s, fd);
	r2 = write(fd, "\n", 1);
	if (r1 < 0 || r2 < 0)
		return (-1);
	return (r1 + r2);
}

int	ft_putnbrn_fd(int n, int fd)
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
	return (ft_putstrn_fd(buf + i, fd));
}
