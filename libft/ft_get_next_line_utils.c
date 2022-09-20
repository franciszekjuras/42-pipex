/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:14:11 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/01 23:15:47 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_get_next_line_utils.h"

/**
 * @brief Return length of string `s` or 0 if `s` is null. 
 * @param s string
 * @return size_t string length
 */
size_t	ft_strlen_null(const char *s)
{
	size_t	i;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief Split string `str` into strings with `n` and `strlen(str) - n`
 * characters. Allocate and return copy of the first string.
 * Move second string into the beggining of `str`. 
 * @param str string to split
 * @param n index to split at
 * @return char* pointer to newly allocated first string (null on malloc error)
 */
char	*ft_strnsplit(char *str, size_t n)
{
	size_t	trail_len;
	char	*lead_str;

	trail_len = ft_strlen_null(str + n);
	lead_str = malloc(sizeof(char) * (n + 1));
	if (lead_str == 0)
		return (0);
	ft_memcpy(lead_str, str, n);
	lead_str[n] = '\0';
	ft_memcpy(str, str + n, trail_len + 1);
	return (lead_str);
}

/**
 * @brief Append `buf` to `node->str`, allocating and deallocating
 * memory as necessary. If `node->str` is null it's treated as empty.
 * After calling this function, node->str will be a valid string
 * except of a malloc error 
 * @param node node with string for appending
 * @param buf buffer with string to append
 * @return int 1 on success, 0 on failure
 */
int	node_appbuf(t_list *node, const char *buf)
{
	char	*dst;
	size_t	str_len;
	size_t	buf_len;

	if (buf[0] == '\0' && node->str != 0)
		return (1);
	str_len = ft_strlen_null(node->str);
	buf_len = ft_strlen_null(buf);
	if (node->size < str_len + buf_len + 1)
	{
		dst = malloc((str_len * 2) + buf_len + 1);
		if (dst == 0)
			return (0);
		ft_memcpy(dst + str_len, buf, buf_len + 1);
		ft_memcpy(dst, node->str, str_len);
		free(node->str);
		node->str = dst;
		node->size = (str_len * 2) + buf_len + 1;
	}
	else
		ft_memcpy(node->str + str_len, buf, buf_len + 1);
	return (1);
}
