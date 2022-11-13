/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/14 03:10:48 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmds.h"
#include "env.h"
#include "cmd_builtin.h"
#include "signal_minishell.h"

int	is_continue(t_cmds *cmds, int rval, size_t i)
{
	if (i > 0)
	{
		if (i > 0 && (cmds[i - 1].operator == D_PIPE && rval == 0) && ++i)
			return (true);
		else if (i > 0 && (cmds[i - 1].operator == D_AMPERSAND \
					&& rval > 0 && rval < 256 && ++i))
			return (true);
	}
	return (false);
}

static int	change_buildin_fd_inout(int fd_inout, char *filename, int option, int *fd)
{
	*fd = fd_inout;
	if (filename)
	{
		close(*fd);
		*fd = open(filename, option);
		if (fd < 0)
		{
			ft_putstr_fd("open error:", 2);
			write(2, filename, ft_strlen(filename)); 
			write(2, "\n", 1);
			return (false);
		}
	}
	if (dup2(*fd, fd_inout) == -1)
		return (false);
	return (true);
}

static int	change_buildin_fd(t_pipe *pipe, int back)
{
	static int	pre_fd_in = 0;
	static int	pre_fd_out = 1;
	static int	fd_in = 0;
	static int	fd_out = 1;

	if (back == false)
	{
		pre_fd_in = dup(pipe->option_fd_in);
		pre_fd_out = dup(pipe->option_fd_out);
		change_buildin_fd_inout(pipe->option_fd_in, pipe->in_file, O_RDONLY, &fd_in);
		change_buildin_fd_inout(pipe->option_fd_out, pipe->out_file, O_APPEND | O_WRONLY, &fd_out);
	}
	if (back == true)
	{
		if (fd_out != 1)
			close(fd_out);
		if (fd_in != 1)
			close(fd_in);
		dup2(pre_fd_in, 0);
		dup2(pre_fd_out, 1);
	}
	return (true);
}

void	exe_cmds(t_cmds *cmds)
{
	size_t	i;
	char	**envv;
	int		rval;

	envv = env_store(NULL, GET_ENV);
	i = 0;
	rval = 0;
	while (&cmds[i])
	{
		if (i > 0 && cmds[i - 1].last)
			break ;
		if (is_continue(cmds, rval, i) && ++i)
			continue ;
		handle_cmd_signals();
		if (cmds[i].len > 1 || (cmds[i].len == 1 \
					&& !cmds[i].pipes[0].is_builtin_cmd))
			rval = pipex(&(cmds[i]), envv);
		else if (change_buildin_fd(&(cmds[i].pipes[0]), false))
		{
			rval = exec_builtin_cmd(cmds[i].pipes[0].param);
			change_buildin_fd(&(cmds[i].pipes[0]), true);
		}
		handle_global_signals();
		set_exit_status(rval);
		i++;
	}
}
