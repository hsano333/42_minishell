/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 03:25:37 by hsano             #+#    #+#             */
/*   Updated: 2022/11/14 22:47:05 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_quote_flag.h"
#include <stdio.h>

static t_token_type	lexer_quote_flag(int mode, t_token_type flag)
{
	static t_token_type	quote_flag = NON;

	if (mode == LEXER_GET_FLAG)
		return (quote_flag);
	else
		quote_flag = flag;
	return (0);
}

t_token_type	get_lexer_quote(void)
{
	return (lexer_quote_flag(LEXER_GET_FLAG, 0));
}

void	set_lexer_quote(t_token_type flag)
{
	lexer_quote_flag(LEXER_SET_FLAG, flag);
}

int	change_quote_type(t_token *tokens, size_t *i, size_t *k)
{
	while (1)
	{
		if (get_lexer_quote() != tokens[*i].type)
		{
			*k -= tokens[*i].len;
			(*i)--;
		}
		else
		{
			tokens[*i].type = IDENT;
			(*i)++;
			(*k) += 1;
			set_lexer_quote(NON);
			return (true);
		}
		if (*i == 0)
			return (false);
	}
	return (true);
}

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
