/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/10/25 01:24:56 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmds.h"

void	exe_cmds(t_cmds *cmds)
{
	size_t	i;
	char	*in_file;
	char	*out_file;
	extern char	**environ;

	i = 0;
	out_file = NULL;
	while (&cmds[i])
	{
		in_file = cmds[i].pipes[0].in_file;
		if (cmds[i].len > 0)
			out_file = cmds[i].pipes[cmds[i].len - 1].out_file;
		pipex(in_file, out_file, &(cmds[i]), environ);

		if (cmds[i].last)
			break ;
		i++;
	}
}
