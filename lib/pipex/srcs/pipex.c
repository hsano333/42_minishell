/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 07:57:07 by hsano             #+#    #+#             */
/*   Updated: 2022/11/14 14:14:26 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
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

static void	exit_main_child(int status)
{
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
}

static void	main_child(t_fdpid *fdpid, t_cmds *cmds, char **environ)
{
	int		i;
	int		fd_i;
	int		status;
	int		tmp_status;

	i = -1;
	fd_i = 1;
	while (++i < (int)cmds->len)
	{
		fdpid[fd_i] = pipe_main(fdpid[fd_i - 1].fd, &(cmds->pipes[i]) \
				, environ, i == (int)cmds->len - 1);
		if (fdpid[fd_i++].pid == -1)
			kill_process(-1, "pipex error:fork() error", NULL);
	}
	close(fdpid[fd_i].fd);
	i = fd_i - 1;
	waitpid(fdpid[i].pid, &status, 0);
	while (i > 0)
	{
		kill(fdpid[i--].exe_pid, SIGINT);
		if (i > 0)
			waitpid(fdpid[i].pid, &tmp_status, 0);
	}
	exit_main_child(status);
}

int	pipex(t_cmds *cmds)
{
	int		pid;
	int		status;
	char	**environ;
	t_fdpid	fdpid[4096];

	environ = env_store(NULL, GET_ENV);
	pid = fork();
	if (pid == 0)
		main_child(fdpid, cmds, environ);
	else if (pid == -1)
		kill_process(-1, NULL, NULL);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
