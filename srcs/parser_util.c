/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:06:55 by hsano             #+#    #+#             */
/*   Updated: 2022/11/10 15:47:53 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stdlib.h"
#include "string.h"
#include "lexer_quote_flag.h"

void	set_lexer_quote_util(t_token_type type)
{
	if (get_lexer_quote() == type)
		set_lexer_quote(NON);
	else if (get_lexer_quote() == NON)
	{
		if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
			set_lexer_quote(type);
	}
}

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
