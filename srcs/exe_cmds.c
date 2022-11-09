/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/09 13:18:09 by maoyagi          ###   ########.fr       */
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
		else
			rval = exec_builtin_cmd(cmds[i].pipes[0].param);
		handle_global_signals();
		set_exit_status(rval);
		i++;
	}
}
