/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 09:58:09 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/01 23:16:02 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libft.h"
#include "ft_printf_utils.h"

static ssize_t	wcheck(ssize_t write_ret, int *err)
{
	if (write_ret < 0)
		*err = -1;
	return (write_ret);
}

int	ft_vdprintf(int fd, const char *fstr, t_ft_va_list *list)
{
	const char		*pos;
	const char		*passed;
	ssize_t			count;
	int				write_err;
	t_printf_format	format;

	count = 0;
	write_err = 0;
	pos = fstr;
	format = ft_scan_format((char **) &pos, (char **) &passed, list);
	while (format.valid)
	{
		count += wcheck(write(fd, fstr, passed - fstr), &write_err);
		count += wcheck(ft_put_format_fd(fd, format, list), &write_err);
		fstr = pos;
		format = ft_scan_format((char **) &pos, (char **) &passed, list);
	}
	count += wcheck(write(fd, fstr, passed - fstr), &write_err);
	if (write_err)
		return (-1);
	return (count);
}

int	ft_printf(const char *fstr, ...)
{
	int				r;
	t_ft_va_list	list;

	va_start(list.args, fstr);
	r = ft_vdprintf(1, fstr, &list);
	va_end(list.args);
	return (r);
}

int	ft_dprintf(int fd, const char *fstr, ...)
{
	int				r;
	t_ft_va_list	list;

	va_start(list.args, fstr);
	r = ft_vdprintf(fd, fstr, &list);
	va_end(list.args);
	return (r);
}
