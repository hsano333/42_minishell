/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/10/31 01:03:27 by hsano            ###   ########.fr       */
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
	while (&cmds[i])
	{
		if (i > 0 && cmds[i - 1].last)
			break ;
		else if (i > 0 && (cmds[i - 1].operator == D_PIPE && rval == 0) && ++i)
			continue ;
					
		else if (i > 0 && (cmds[i - 1].operator == D_AMPERSAND && rval >  0 && rval < 256 && ++i))
			continue ;
		in_file = cmds[i].pipes[0].in_file;
		if (cmds[i].len > 0)
			out_file = cmds[i].pipes[cmds[i].len - 1].out_file;
		printf("exe_cmds:outfile:%s\n", out_file);
		rval = pipex(in_file, out_file, &(cmds[i]), environ);
		printf("rval=%d\n", rval);
		set_exit_status(rval);
		i++;
	}
}
