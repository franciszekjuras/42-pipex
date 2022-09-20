/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:16:16 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/28 12:32:43 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_pathjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;
	int		add_slash;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	add_slash = (s1_len > 0 && s1[s1_len - 1] != '/');
	dst = malloc(s1_len + s2_len + add_slash + 1);
	if (dst == 0)
		return (0);
	ft_memcpy(dst, s1, s1_len);
	ft_memcpy(dst + s1_len + add_slash, s2, s2_len + 1);
	if (add_slash)
		dst[s1_len] = '/';
	return (dst);
}
