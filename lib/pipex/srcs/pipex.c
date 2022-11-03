/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/11/03 18:25:55 by hsano            ###   ########.fr       */
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
#include "signal_minishell.h"

static void	change_fd(int *pipe_fd, t_pipe *pipes, int is_last)
{
	if (is_last && !pipes->out_file)
	{
		close(pipe_fd[PIPE_OUT]);
		pipe_fd[PIPE_OUT] = 1;
	}
	else if (pipes->out_file)
	{
		close(pipe_fd[PIPE_OUT]);
		pipe_fd[PIPE_OUT] = open(pipes->out_file, pipes->write_option);
		//printf("outfile open :%s, pipe_fd[PIPE_OUT]=%d\n",pipes->out_file,  pipe_fd[PIPE_OUT]);
		if (pipe_fd[PIPE_OUT] < 0)
			kill_process(-1, pipes->out_file, NULL);
	}

}

static t_fdpid	pipe_main(int fd_in, t_pipe *pipes, char **environ, int is_last)
{
	int		pipe_fd[2];
	t_fdpid	fdpid;

	fdpid.pid = -1;
	if (pipe(pipe_fd) != 0)
		return (fdpid);
	change_fd(pipe_fd, pipes, is_last);
	fdpid.pid = fork();
	if (fdpid.pid == 0)
	{
		close(pipe_fd[PIPE_IN]);
		child(fd_in, pipe_fd, pipes, environ);
		exit(0);
	}
	else if (fdpid.pid > 0)
	{
		if (pipe_fd[PIPE_OUT] != 1)
			close(pipe_fd[PIPE_OUT]);
		fdpid = parent(fdpid.pid, pipe_fd, pipes, is_last);
	}
	if (fd_in > 0)
		close(fd_in);
	return (fdpid);
}

static void	main_child(t_fdpid *fdpid, t_cmds *cmds, char **environ)
{
	int		i;
	int		fd_i;
	int		status;

	i = 0;
	fd_i = 1;
	while (i < (int)cmds->len)
	{
		fdpid[fd_i] = pipe_main(fdpid[fd_i - 1].fd, &(cmds->pipes[i]), environ, i == (int)cmds->len - 1);
		i++;
		if (fdpid[fd_i].pid == -1)
			kill_process(-1, "pipex error:fork() error", NULL);
		fd_i++;
	}
	//todo
	//printf("pre write fd_i=%d, fdpid[0]=%d,fdpid[%d]=%d \n", fd_i, fdpid[0].fd, fd_i-1, fdpid[fd_i - 1].fd);
	//if (output_file)
		//write_file(fdpid[fd_i - 1].fd, output_file);
	//else
		//waitpid(fdpid[i].pid, &status, 0);
	close(fdpid[fd_i].fd);
	i = 1;
	while (i < fd_i)
	{
		waitpid(fdpid[i++].pid, &status, 0);
	}
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
}

int	pipex(t_cmds *cmds, char **environ)
{
	int		pid;
	int		status;
	t_fdpid	fdpid[4096];

	////fdpid[0].fd = 0;
	///if (fdpid[0].fd == -1)
		//kill_process(-1, input_file, NULL);
	pid = fork();
	if (pid == 0)
	{
		//set_signal(CHILD_MODE);
		main_child(fdpid, cmds, environ);
	}
	else if (pid == -1)
		kill_process(-1, NULL, NULL);
	waitpid(pid, &status, 0);
	//g_pid = pid;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
