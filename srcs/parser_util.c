/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:06:55 by hsano             #+#    #+#             */
/*   Updated: 2022/10/27 16:15:18 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stdlib.h"

int	is_error_cmds(t_cmds *cmds)
{
	size_t	i;

	if (!cmds)
		return (false);
	i = 0;
	while (cmds)
	{
		if (cmds[i].pipes == NULL)
			break ;
		if (cmds[i].last == true)
			return (false);
		i++;
	}
	return (true);
}

#include <stdio.h>

void	clear_all_cmds(t_cmds **cmds)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*cmds)
	{
		j = 0;
		while (j < (*cmds)[i].len)
		{
			free((*cmds)[i].pipes[j].param);
			(*cmds)[i].pipes[j].param = NULL;
			j++;
		}
		free((*cmds)[i].pipes);
		(*cmds)[i].pipes = NULL;
		if ((*cmds)[i].last == true)
			break ;
		i++;
	}
	free(*cmds);
	*cmds = NULL;
}
