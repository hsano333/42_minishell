/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/13 12:42:57 by hsano            ###   ########.fr       */
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

static int	change_buidin_fd(t_pipe *pipe, int back)
{
	static int	pre_fd_in = 0;
	static int	pre_fd_out = 1;

	if (back == false && pipe->option_fd_in != 0)
	{
		pre_fd_in = dup(0);
		close(0);
		dup2(pipe->option_fd_in, 0);
	}
	else if (back == true)
		dup2(0, pipe->option_fd_in);
	if (back == false && pipe->option_fd_out != 0)
	{
		pre_fd_out = dup(0);
		close(0);
		dup2(pipe->option_fd_out, 1);
	}
	else if (back == true)
		dup2(1, pipe->option_fd_out);
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
		else if (change_buidin_fd(&(cmds[i].pipes[0]), false))
			rval = exec_builtin_cmd(cmds[i].pipes[0].param);
		handle_global_signals();
		change_buidin_fd(&(cmds[i].pipes[0]), true);
		set_exit_status(rval);
		i++;
	}
}
