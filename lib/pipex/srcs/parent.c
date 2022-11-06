/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:57:10 by hsano             #+#    #+#             */
/*   Updated: 2022/11/06 20:56:18 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parent.h"

static void	parent_child(int pid, int *pipe_fd, int *pipe_fd_p, t_pipe *pipes)
{
	int		status;
	int		fd;
	char	buf[READ_MAX];
	size_t	read_size;

	fd = pipe_fd_p[PIPE_OUT];
	if (pipes->out_file)
	{
		close(pipe_fd_p[PIPE_OUT]);
		fd = open(pipes->out_file, pipes->write_option);
	}
	while (1)
	{
		read_size = read(pipe_fd[PIPE_IN], buf, READ_MAX);
		if (read_size > 0)
			write(fd, buf, read_size);
		else if (read_size <= 0)
		{
			close(fd);
			waitpid(pid, &status, 0);
			break ;
		}
	}
}

t_fdpid	pranet_parent(int pid, t_fdpid fdpid, int *pipe_fd_p, int flag)
{
	close(pipe_fd_p[PIPE_OUT]);
	fdpid.fd = pipe_fd_p[PIPE_IN];
	if (flag)
		fdpid.fd = pipe_fd_p[PIPE_IN];
	else
		fdpid.pid = pid;
	return (fdpid);
}

t_fdpid	parent(int pid, int *pipe_fd, t_pipe *pipes, int is_last)
{
	int		pipe_fd_p[2];
	t_fdpid	fdpid;

	if (pipe(pipe_fd_p) != 0)
		kill_process(0, "parent():pipe() error\n", NULL);
	fdpid.pid = fork();
	if ((fdpid.pid) == 0)
	{
		close(pipe_fd_p[PIPE_IN]);
		if (!pipes->out_file && !is_last)
			parent_child(pid, pipe_fd, pipe_fd_p, pipes);
		else
			close(pipe_fd_p[PIPE_OUT]);
		close(pipe_fd[PIPE_IN]);
		exit(0);
	}
	else if (fdpid.pid > 0)
	{
		close(pipe_fd[PIPE_IN]);
		fdpid = pranet_parent(pid, fdpid, pipe_fd_p \
						, (!pipes->out_file && !is_last));
	}
	return (fdpid);
}
