/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/10/28 01:25:15 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmds.h"

void	exe_cmds(t_cmds *cmds)
{
	size_t	i;
	char	*in_file;
	char	*out_file;
	extern char	**environ;
	int	rval;

	i = 0;
	out_file = NULL;
	rval = 1023;
	while (&cmds[i])
	{
		if (cmds[i].operator == D_PIPE && rval == true && i++)
			continue ;
		else if (cmds[i].operator == D_AMPERSAND && rval == false && i++)
			continue ;
		in_file = cmds[i].pipes[0].in_file;
		if (cmds[i].len > 0)
			out_file = cmds[i].pipes[cmds[i].len - 1].out_file;
		rval = pipex(in_file, out_file, &(cmds[i]), environ);
		set_exit_status(rval);
		if (cmds[i].last)
			break ;
		i++;
	}
}
