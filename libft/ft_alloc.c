/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:38:55 by fjuras            #+#    #+#             */
/*   Updated: 2022/04/27 14:47:41 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*mem;

	if (size != 0 && SIZE_MAX / size < number)
		return (0);
	mem = malloc(number * size);
	if (mem == 0)
		return (0);
	ft_bzero(mem, number * size);
	return (mem);
}

void	*ft_freeparr(void **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
		free(arr[i++]);
	free(arr);
	return (0);
}

char	*ft_stralloc(size_t len)
{
	return (ft_calloc(len + 1, sizeof(char)));
}
