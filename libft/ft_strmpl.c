/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmpl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:15:40 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/01 13:03:09 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = malloc(s1_len + s2_len + 1);
	if (dst == 0)
		return (0);
	ft_memcpy(dst, s1, s1_len);
	ft_memcpy(dst + s1_len, s2, s2_len + 1);
	return (dst);
}

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(str);
	while (ft_isinset(str[i], set))
		i++;
	while (j > i && ft_isinset(str[j - 1], set))
		j--;
	return (ft_substr(str, i, j - i));
}

static int	next_word(char **beg, char **end, char delim)
{
	char	*pos;

	pos = *end;
	if (delim != 0)
		while (*pos == delim)
			pos += 1;
	if (*pos == 0)
		return (0);
	*beg = pos;
	while (*pos != delim && *pos != 0)
		pos += 1;
	*end = pos;
	return (1);
}

char	**ft_split(char const *str, char delim)
{
	char	*beg;
	char	*end;
	int		count;
	char	**words;

	end = (char *) str;
	count = 0;
	while (next_word(&beg, &end, delim))
		count += 1;
	words = malloc((count + 1) * sizeof(char *));
	if (words == 0)
		return (0);
	end = (char *) str;
	count = 0;
	while (next_word(&beg, &end, delim))
	{
		words[count] = ft_strndup(beg, end - beg);
		if (words[count] == 0)
			return ((char **) ft_freeparr((void **) words));
		count += 1;
	}
	words[count] = 0;
	return (words);
}
