/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:03:46 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/03 15:17:41 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include <stdarg.h>

# define FT_PRINTF_FLAGS "-+ #0"
# define FT_PRINTF_SPECS "csdiuxXobp"
# define FT_PRINTF_BUF 128

enum e_printf_flag
{
	FT_PRINTF_LJUST = 0x01,
	FT_PRINTF_SIGN = 0x02,
	FT_PRINTF_SPACE = 0x04,
	FT_PRINTF_ALT = 0x08,
	FT_PRINTF_0PAD = 0x10,
};

typedef struct s_printf_format
{
	int		flags;
	int		width;
	int		precision;
	char	specifier;
	char	valid;
}	t_printf_format;

typedef struct s_ft_va_list
{
	va_list	args;
}	t_ft_va_list;

int				ft_vdprintf(int fd, const char *fstr, t_ft_va_list *list);
int				ft_put_format_fd(
					int fd, t_printf_format format, t_ft_va_list *list);
t_printf_format	ft_scan_format(char **pos, char **passed, t_ft_va_list *list);
int				ft_putstr_format_fd(char *str, int fd, t_printf_format format);
int				ft_putunsigned_format_fd(
					t_ft_va_list *list, int fd, t_printf_format format);
int				ft_putsigned_format_fd(
					t_ft_va_list *list, int fd, t_printf_format format);
int				ft_putptr_format_fd(void *ptr, int fd, t_printf_format format);

#endif
