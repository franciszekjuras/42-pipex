/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:20:47 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/01 23:15:54 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdarg.h>
#include "libft.h"
#include "ft_printf_utils.h"

static int	ft_scan_flags(char **pos)
{
	const char	*crr;
	int			flagidx;
	int			flags;

	crr = *pos;
	flags = 0;
	flagidx = ft_idxinset(*crr, FT_PRINTF_FLAGS);
	while (flagidx >= 0)
	{
		flags |= (1 << flagidx);
		crr++;
		flagidx = ft_idxinset(*crr, FT_PRINTF_FLAGS);
	}
	*pos = (char *) crr;
	return (flags);
}

static int	ft_parse_number(
	char **pos, t_ft_va_list *list, t_printf_format *format)
{
	int	n;
	int	err;

	err = 0;
	if (**pos == '*')
	{
		n = va_arg(list->args, int);
		*pos += 1;
	}
	else
		n = ft_strtonum(pos, 0, INT_MAX, &err);
	if (err)
		return (-1);
	if (n < 0)
	{
		if (format != 0)
		{
			format->flags |= FT_PRINTF_LJUST;
			n = -n;
		}
		else
			return (-1);
	}
	return (n);
}

static void	ft_parse_format(
	t_printf_format *format, char **pos, t_ft_va_list *list)
{
	format->flags = ft_scan_flags(pos);
	if (ft_isdigit(**pos) || **pos == '*')
		format->width = ft_parse_number(pos, list, format);
	else
		format->width = -1;
	if (**pos == '.')
	{
		*pos += 1;
		if (ft_isdigit(**pos) || **pos == '*')
			format->precision = ft_parse_number(pos, list, 0);
		else
			format->precision = 0;
	}
	else
		format->precision = -1;
	if (**pos == '%' || ft_isinset(**pos, FT_PRINTF_SPECS))
	{
		format->specifier = *((*pos)++);
		format->valid = 1;
	}
}

t_printf_format	ft_scan_format(char **pos, char **passed, t_ft_va_list *list)
{
	t_printf_format	format;

	format.valid = 0;
	format.width = -1;
	format.precision = -1;
	while (!format.valid)
	{
		while (**pos != '\0' && **pos != '%')
			(*pos)++;
		*passed = (char *) *pos;
		if (**pos == '\0')
			return (format);
		(*pos)++;
		ft_parse_format(&format, pos, list);
	}
	return (format);
}
