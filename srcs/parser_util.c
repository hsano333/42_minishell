/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:06:55 by hsano             #+#    #+#             */
/*   Updated: 2022/11/14 22:38:22 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stdlib.h"
#include "string.h"
#include "libft_str.h"
#include "lexer_quote_flag.h"

int	is_error_cmds(t_cmds *cmds)
{
	size_t	i;

	if (!cmds)
	{
		strerror(12);
		return (false);
	}
	i = 0;
	while (cmds)
	{
		if (cmds[i].pipes == NULL)
			break ;
		if (cmds[i].last == true)
		{
			strerror(12);
			return (false);
		}
		i++;
	}
	return (true);
}

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
			if ((*cmds)[i].pipes[j].have_param)
				ft_free_split((*cmds)[i].pipes[j].param);
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

size_t	pass_space(t_token *tokens, size_t i)
{
	int	flag;

	flag = false;
	i++;
	while (tokens[i].type == WHITE_SPACE)
	{
		flag = true;
		i++;
	}
	if (flag)
		return (i - 1);
	return (i);
}
