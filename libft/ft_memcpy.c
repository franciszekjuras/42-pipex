/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:06:21 by fjuras            #+#    #+#             */
/*   Updated: 2022/02/28 15:18:11 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *) dst;
	s = (const unsigned char *) src;
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (dst > src)
	{
		while (i < len)
		{
			d[len - i - 1] = s[len - i - 1];
			i++;
		}
	}
	return (dst);
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	return (ft_memmove(dst, src, len));
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	const void	*src_pos;
	size_t		copy_len;

	src_pos = ft_memchr(src, c, len);
	if (src_pos == 0)
		copy_len = len;
	else
		copy_len = (src_pos - src + 1);
	ft_memmove(dst, src, copy_len);
	if (src_pos == 0)
		return (0);
	return (dst + copy_len);
}
