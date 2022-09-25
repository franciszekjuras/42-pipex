/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:32:23 by fjuras            #+#    #+#             */
/*   Updated: 2022/09/25 14:24:29 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libft/libft.h>

extern char	**environ;

pid_t	execute_clean_up(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
	return (-1);
}

pid_t	execute_with_custom_io(char *cmd, int fd_in, int fd_out)
{
	char	**args;
	char	*prog;
	pid_t	child;

	if (fd_in < 0 || fd_out < 0)
		return (execute_clean_up(fd_in, fd_out));
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
	ft_freeparr((void **)args);
	close(fd_in);
	close(fd_out);
	return (child);
}

int	get_retval_from_exit_status(int exit_status)
{
	if (!WIFSIGNALED(exit_status))
		return (WEXITSTATUS(exit_status));
	else
		return (128 + WTERMSIG(exit_status));
}

int	wait_until_all_children_exit(int children_number, pid_t last_child)
{
	int		i;
	int		retval;
	int		exited_status;
	pid_t	exited_pid;

	retval = 0;
	i = 0;
	while (i < children_number)
	{
		exited_pid = wait(&exited_status);
		if (exited_pid == last_child)
		{			
			retval = get_retval_from_exit_status(exited_status);
		}
		++i;
	}
	return (retval);
}

int	open_with_error_print(char *progname, char *file, int flags)
{
	int	fd;

	if (flags == O_RDONLY)
		fd = open(file, flags);
	else
		fd = open(file, flags, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: %s\n", progname, file, strerror(errno));
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	pid_t	last_child;
	int		file_in;
	int		file_out;
	int		pipe_fds[2];

	(void) argc;
	pipe(pipe_fds);
	file_in = open_with_error_print(argv[0], argv[1], O_RDONLY);
	file_out = open_with_error_print(
			argv[0], argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	last_child = execute_with_custom_io(argv[2], file_in, pipe_fds[1]);
	last_child = execute_with_custom_io(argv[3], pipe_fds[0], file_out);
	return (wait_until_all_children_exit(2, last_child));
}
