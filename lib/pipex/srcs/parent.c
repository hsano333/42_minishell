/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:57:10 by hsano             #+#    #+#             */
/*   Updated: 2022/11/01 14:54:35 by hsano            ###   ########.fr       */
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
		//return ;
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

t_fdpid	parent(int pid, int *pipe_fd, t_pipe *pipes, int is_last)
{
	int		pipe_fd_p[2];
	//int		status;
	t_fdpid	fdpid;

	//printf("is_last=%d\n", is_last);
	if (pipe(pipe_fd_p) != 0)
		kill_process(0, "parent():pipe() error\n", NULL);
	fdpid.pid = fork();
	if ((fdpid.pid) == 0)
	{
		close(pipe_fd_p[PIPE_IN]);
		//if ((!is_last || (is_last && pipes->out_file)))
		if (!pipes->out_file && !is_last)
		{
			//printf("parent_child No.,1\n");
			parent_child(pid, pipe_fd, pipe_fd_p, pipes);
		}
		else
		{
			close(pipe_fd_p[PIPE_OUT]);
			//waitpid(pid, &status, 0);
			//fdpid.pid = pid;
		}
		close(pipe_fd[PIPE_IN]);
		exit(0);
	}
	else if (fdpid.pid > 0)
	{
		close(pipe_fd[PIPE_IN]);
		close(pipe_fd_p[PIPE_OUT]);
		fdpid.fd = pipe_fd_p[PIPE_IN];
		//if ((!is_last && !pipes->out_file))
		//if (!pipes->out_file)
		if (!pipes->out_file && !is_last)
		{
			fdpid.fd = pipe_fd_p[PIPE_IN];

		}
		else
		{
			//fdpid.fd = 0;
			fdpid.pid = pid;
		}
	}
	return (fdpid);
}
