/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:14:31 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/22 12:33:40 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	ft_argparse_arg_id(char *arg)
{
	if (arg[0] == '-')
	{
		if (ft_isalpha(arg[1]) || arg[1] == '-')
			return (arg[1]);
	}
	return ('\0');
}

static int	ft_argparse_next(
			int argc, char **argv, int beg, t_ft_argparse *arg)
{
	int	i;
	int	params;

	params = 0;
	arg->arg = ft_argparse_arg_id(argv[beg]);
	if (arg->arg == '\0')
		arg->arg = '-';
	else
		++beg;
	while (beg + params < argc && ft_argparse_arg_id(argv[beg + params]) == 0)
		++params;
	arg->count = params;
	arg->params = ft_calloc(params + 1, sizeof(char *));
	i = 0;
	while (i < params)
	{
		arg->params[i] = ft_strdup(argv[beg + i]);
		++i;
	}
	arg->params[i] = NULL;
	return (beg + params);
}

t_ft_argparse	*ft_argparse(int argc, char **argv)
{
	int				i;
	int				arg_idx;
	int				args_number;
	t_ft_argparse	*args;

	i = 1;
	args_number = 0;
	if (argc > 1 && argv[1][0] != '-')
		++args_number;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
			++args_number;
		++i;
	}
	args = ft_calloc(args_number + 1, sizeof(t_ft_argparse));
	i = 1;
	arg_idx = 0;
	while (i < argc)
	{
		i = ft_argparse_next(argc, argv, i, args + arg_idx);
		++arg_idx;
	}
	return (args);
}

t_ft_argparse	*ft_argparse_find(t_ft_argparse *args, char arg)
{
	while (args->arg != 0 && args->arg != arg)
		++args;
	if (args->arg == 0)
		return (NULL);
	return (args);
}

t_ft_argparse	*ft_argparse_free(t_ft_argparse *args)
{
	int	i;

	i = 0;
	while (args[i].arg != 0)
		ft_freeparr((void **)args[i++].params);
	free(args);
	return (NULL);
}
