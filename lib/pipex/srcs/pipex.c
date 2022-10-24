/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/10/25 02:35:26 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "parent.h"
#include "child.h"
#include "write_file.h"
#include "libft_str.h"
#include "ft_printf.h"
#include "heredoc.h"
#include "pipex_util.h"

static t_fdpid	pipe_main( int fd_in, t_pipe *pipes, char **environ)
{
	int		pipe_fd[2];
	t_fdpid	fdpid;

	fdpid.pid = -1;
	if (pipe(pipe_fd) != 0)
		return (fdpid);
	fdpid.pid = fork();
	if (fdpid.pid == 0)
	{
		close(pipe_fd[PIPE_IN]);
		child(fd_in, pipe_fd, pipes, environ);
		exit(0);
	}
	else if (fdpid.pid > 0)
	{
		close(pipe_fd[PIPE_OUT]);
		fdpid = parent(fdpid.pid, pipe_fd, pipes);
	}
	if (fd_in > 0)
		close(fd_in);
	return (fdpid);
}

static void	main_child(char *output_file, t_fdpid *fdpid, \
		t_cmds *cmds, char **environ)
{
	int		i;
	int		fd_i;
	int		status;

	i = 0;
	fd_i = 0;
	while (i < (int)cmds->len)
	{
		fd_i++;
		fdpid[fd_i] = pipe_main(fdpid[fd_i - 1].fd, &(cmds->pipes[i++]), environ);
		if (fdpid[fd_i].pid == -1)
			kill_process(-1, "pipex error:fork() error", NULL);
	}
	printf("output_file:%s\n", output_file);
	write_file(fdpid[fd_i].fd, output_file);
	i = fd_i;
	while (i > 0)
	{
		waitpid(fdpid[i].pid, &status, 0);
		i--;
	}
}

int	pipex(char *input_file, char *output_file, t_cmds *cmds, char **environ)
{
	int		pid;
	int		status;
	t_fdpid	fdpid[4096];

	fdpid[0].fd = 0;
	//if (input_file)
		//fdpid[0].fd = open(input_file, O_RDONLY);
	if (fdpid[0].fd == -1)
		kill_process(-1, input_file, NULL);
	pid = fork();
	if (pid == 0)
	{
		main_child(output_file, fdpid, cmds, environ);
		exit(0);
	}
	else if (pid == -1)
		kill_process(-1, NULL, NULL);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		kill_process(0, NULL, NULL);
	return (0);
}
