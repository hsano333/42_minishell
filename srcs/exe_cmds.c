/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/03 22:40:13 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmds.h"
#include "env.h"
#include "cmd_builtin.h"

void	exe_cmds(t_cmds *cmds)
{
	size_t	i;
	//char	*in_file;
	//char	*out_file;
	//extern char	**environ;
	char **envv;

	
	envv = env_store(NULL, GET_ENV);
	int	rval;

	i = 0;
	rval = 0;
	//out_file = NULL;
	while (&cmds[i])
	{
		if (i > 0)
		{
			if (i > 0 && cmds[i - 1].last)
				break ;
			else if (i > 0 && (cmds[i - 1].operator == D_PIPE && rval == 0) && ++i)
				continue ;
			else if (i > 0 && (cmds[i - 1].operator == D_AMPERSAND && rval >  0 && rval < 256 && ++i))
				continue ;
		}
		if (cmds[i].len > 1 || (cmds[i].len == 1 && !cmds[i].pipes[0].is_builtin_cmd))
		{
			rval = pipex(&(cmds[i]), envv);
		}
		else
		{
			rval = exec_builtin_cmd(cmds[i].pipes[0].param);
		}
		set_exit_status(rval);
		i++;
	}
}
