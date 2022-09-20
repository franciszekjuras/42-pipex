/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:03:43 by fjuras            #+#    #+#             */
/*   Updated: 2022/03/19 15:04:28 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c + ('A' - 'a'));
	return (c);
}

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

char	*ft_strtoupper(char *s)
{
	char	*c;

	c = s;
	while (*c != '\0')
	{
		if (*c >= 'a' && *c <= 'z')
			*c += 'A' - 'a';
		c++;
	}
	return (s);
}

char	*ft_strtolower(char *s)
{
	char	*c;

	c = s;
	while (*c != '\0')
	{
		if (*c >= 'A' && *c <= 'Z')
			*c += 'a' - 'A';
		c++;
	}
	return (s);
}
