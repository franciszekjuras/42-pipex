/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:20:47 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/03 15:15:46 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf_utils.h"

static char	*ft_getnumprefix(char s)
{
	if (s == 'x')
		return ("0x");
	else if (s == 'X')
		return ("0X");
	else if (s == 'o')
		return ("0");
	else if (s == 'b')
		return ("b");
	return ("");
}

static int	ft_putnbrcmn_format_fd(
	char *prefix, char *content, int fd, t_printf_format format)
{
	int	pad;
	int	zeros;
	int	r[4];
	int	len[2];

	len[0] = ft_strlen(prefix);
	len[1] = ft_strlen(content);
	zeros = ft_max(0, format.precision - len[1]);
	if (zeros > 0 && ft_strcmp(prefix, "0") == 0)
		--zeros;
	pad = ft_max(0, format.width - (len[0] + zeros + len[1]));
	if (format.flags & FT_PRINTF_0PAD && pad > 0 && format.precision < 0
		&& !(format.flags & FT_PRINTF_LJUST))
		ft_swapi(&pad, &zeros);
	if (!(format.flags & FT_PRINTF_LJUST))
		r[0] = ft_putncharn_fd(' ', pad, fd);
	r[1] = ft_putstrn_fd(prefix, fd);
	r[2] = ft_putncharn_fd('0', zeros, fd);
	r[3] = ft_putstrn_fd(content, fd);
	if (format.flags & FT_PRINTF_LJUST)
		r[0] = ft_putncharn_fd(' ', pad, fd);
	if (r[0] < 0 || r[1] < 0 || r[2] < 0 || r[3] < 0)
		return (-1);
	return (r[0] + r[1] + r[2] + r[3]);
}

int	ft_putunsigned_format_fd(
	t_ft_va_list *list, int fd, t_printf_format format)
{
	char				buf[FT_PRINTF_BUF];
	unsigned long long	nbr;
	char				*prefix;
	char				*content;

	nbr = va_arg(list->args, unsigned int);
	if (format.precision == 0 && nbr == 0)
		content = "";
	else if (format.specifier == 'x' || format.specifier == 'X')
		content = ft_ulltoa_base_buf(nbr, 16, buf, FT_PRINTF_BUF);
	else if (format.specifier == 'u')
		content = ft_ulltoa_base_buf(nbr, 10, buf, FT_PRINTF_BUF);
	else if (format.specifier == 'o')
		content = ft_ulltoa_base_buf(nbr, 8, buf, FT_PRINTF_BUF);
	else if (format.specifier == 'b')
		content = ft_ulltoa_base_buf(nbr, 2, buf, FT_PRINTF_BUF);
	else
		return (-1);
	if (format.specifier == 'X')
		content = ft_strtoupper(content);
	prefix = "";
	if (format.flags & FT_PRINTF_ALT && nbr != 0)
		prefix = ft_getnumprefix(format.specifier);
	return (ft_putnbrcmn_format_fd(prefix, content, fd, format));
}

int	ft_putsigned_format_fd(
	t_ft_va_list *list, int fd, t_printf_format format)
{
	char		buf[FT_PRINTF_BUF];
	long long	nbr;
	int			sign;
	char		*prefix;
	char		*content;

	nbr = va_arg(list->args, int);
	sign = 1;
	if (nbr < 0)
		sign = -1;
	if (format.precision == 0 && nbr == 0)
		content = "";
	else
		content = ft_ulltoa_base_buf(ft_absull(nbr), 10, buf, FT_PRINTF_BUF);
	prefix = "";
	if (sign < 0)
		prefix = "-";
	else if (format.flags & FT_PRINTF_SIGN)
		prefix = "+";
	else if (format.flags & FT_PRINTF_SPACE)
		prefix = " ";
	return (ft_putnbrcmn_format_fd(prefix, content, fd, format));
}

int	ft_putptr_format_fd(void *ptr, int fd, t_printf_format format)
{
	unsigned long long	ptri;
	char				*content;
	char				buf[FT_PRINTF_BUF];

	ptri = (unsigned long long) ptr;
	format.flags &= FT_PRINTF_LJUST;
	content = ft_ulltoa_base_buf(ptri, 16, buf, FT_PRINTF_BUF);
	return (ft_putnbrcmn_format_fd("0x", content, fd, format));
}
