/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:21:08 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/27 13:01:08 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_UTILS_H
# define APP_UTILS_H

# include <sys/types.h>
# include "app.h"

char	**extract_path_arr_from_env(void);
int		check_if_path_is_executable(char *path, char *prog, char **candidate);
char	*resolve_prog_path(t_app *app, char *prog);
pid_t	exec_clean_up(char **args, int fd_in, int fd_out);

#endif
