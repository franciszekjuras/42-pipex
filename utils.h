/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:21:08 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/29 18:40:49 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char	**extract_path_arr_from_env(void);
int		check_if_path_is_executable(char *path, char *prog, char **candidate);

#endif
