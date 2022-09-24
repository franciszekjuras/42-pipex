/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:32:23 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/24 14:44:57 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libft/libft.h>

extern char	**environ;

pid_t	execute_with_custom_io(char *cmd, int fd_in, int fd_out)
{
	char	**args;
	char	*prog;
	pid_t	child;

	args = ft_split(cmd, ' ');
	prog = args[0];
	child = fork();
	if (child == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		execve(prog, args, environ);
		exit(errno);
	}
	close(fd_in);
	close(fd_out);
	return (child);
}

int	main(int argc, char **argv)
{
	pid_t	child;
	pid_t	exited_pid;
	int		exited_status;
	int		retval;
	int		file_in;
	int		file_out;

	(void) argc;
	(void) child;
	(void) exited_pid;

	file_in = open(argv[1], O_RDONLY);
	file_out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	child = execute_with_custom_io(argv[2], file_in, file_out);
	exited_pid = wait(&exited_status);
	if (!WIFSIGNALED(exited_status))
		retval = WEXITSTATUS(exited_status);
	else
		retval = 128 + WTERMSIG(exited_status);
	return (retval);
}
