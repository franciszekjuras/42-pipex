/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:20:47 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/01 23:16:08 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf_utils.h"

int	ft_putstr_format_fd(char *str, int fd, t_printf_format format)
{
	int		len;
	int		pad;
	int		r[2];

	if (str == 0)
		str = "(null)";
	if (format.specifier == 'c')
		len = 1;
	else if (format.precision >= 0)
		len = ft_strnlen(str, format.precision);
	else
		len = ft_strlen(str);
	pad = ft_max(0, format.width - len);
	if (!(format.flags & FT_PRINTF_LJUST))
		r[0] = ft_putncharn_fd(' ', pad, fd);
	r[1] = write(fd, str, len);
	if (format.flags & FT_PRINTF_LJUST)
		r[0] = ft_putncharn_fd(' ', pad, fd);
	if (r[0] < 0 || r[1] < 0)
		return (-1);
	return (r[0] + r[1]);
}

int	ft_put_format_fd(int fd, t_printf_format format, t_ft_va_list *list)
{
	char	c;

	if (format.specifier == 'c')
	{
		c = (char) va_arg(list->args, int);
		return (ft_putstr_format_fd(&c, fd, format));
	}
	else if (format.specifier == 's')
		return (ft_putstr_format_fd(va_arg(list->args, char *), fd, format));
	else if (ft_isinset(format.specifier, "di"))
		return (ft_putsigned_format_fd(list, fd, format));
	else if (ft_isinset(format.specifier, "uxXob"))
		return (ft_putunsigned_format_fd(list, fd, format));
	else if (format.specifier == 'p')
		return (ft_putptr_format_fd(va_arg(list->args, void *), fd, format));
	else if (format.specifier == '%')
		return (ft_putcharn_fd('%', fd));
	return (-1);
}
