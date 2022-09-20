/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:34:32 by fjuras            #+#    #+#             */
/*   Updated: 2022/02/28 19:39:19 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned char		*p;
	size_t				i;
	unsigned char		uc;

	p = (unsigned char *) b;
	uc = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		if (p[i] == uc)
			return (p + i);
		i++;
	}
	return (0);
}

void	*ft_memrchr(const void *b, int c, size_t len)
{
	unsigned char		*p;
	size_t				i;
	unsigned char		uc;

	p = (unsigned char *) b;
	uc = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		if (p[len - i - 1] == uc)
			return (p + len - i - 1);
		i++;
	}
	return (0);
}

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	const unsigned char	*c1;
	const unsigned char	*c2;
	size_t				i;

	c1 = (const unsigned char *) b1;
	c2 = (const unsigned char *) b2;
	i = 0;
	while (i < len)
	{
		if (c1[i] != c2[i])
			return ((int) c1[i] - (int) c2[i]);
		i++;
	}
	return (0);
}
