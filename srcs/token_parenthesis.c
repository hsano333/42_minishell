/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:59:16 by hsano             #+#    #+#             */
/*   Updated: 2022/11/16 01:40:07 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parenthesis.h"
#include "lexer_quote_flag.h"
#include "lexer.h"
#include "lexer_util.h"
#include "parser.h"
#include "libft_put.h"
#define E_MSG "minishell:syntax error near unexpected token `)'\n"

static int	check_closed(t_token *tokens, size_t *i, int *error)
{
	while (tokens[*i].type != EOS)
	{
		if (tokens[*i].type == RPAREN)
		{
			if (*i > 0 && (tokens[*i - 1].type != IDENT))
				*error = true;
			return (true);
		}
		(*i)++;
	}
	return (false);
}

int	have_paren_error(t_token *tokens)
{
	size_t  i;
	int     closed;
	int     error;

	i = 0;
	error = false;
	closed = true;
	while (tokens[i].type != EOS)
	{
		if (get_lexer_quote() == NON)
		{
			if (tokens[i].type == LPAREN)
				closed = check_closed(tokens, &i, &error);
			else if (tokens[i].type == RPAREN)
				error = true;
		}
		set_lexer_quote_util(tokens[i].type);
		if (!closed)
			ft_putstr_fd("minishell:not closed parenthesis\n", 2);
		if (error)
			ft_putstr_fd(E_MSG, 2);
		if (!closed || error)
			return (true);
		i++;
	}
	return (false);
}


void	enable_paren_token(t_cmds *cmds)
{
	size_t	k;
	size_t	j;

	if (!cmds || !cmds->has_subshell)
		return ;
	k = 0;
	j = 0;
	while (k < cmds->len)
	{
		while (j < cmds->pipes[k].sub_tokens_size)
		{
			cmds->pipes[k].sub_tokens[j].valid = true;
			j++;
		}
		k++;
	}
}

size_t	set_paren(t_token *tokens, t_cmds *cmds, size_t i, size_t pi)
{
	size_t	cnt;

	//printf("set_parent: i=%zu, pi=%zu, type=%d\n", i, pi, tokens[i].type);
	//put_tokens(tokens);
	cnt = 0;
	cmds->pipes[pi].sub_tokens = &(tokens[++i]);
	cmds->has_subshell = true;
	cmds->pipes[pi].is_subshell = true;
	cmds->pipes[pi].subshell_error = false;
	while ((tokens[i].type != EOS && tokens[i].type != RPAREN) && ++i)
		cnt++;
	//printf("cnt=%zu\n", cnt);
	if (tokens[i].type == RPAREN && tokens[i - 1].type != LPAREN)
		cmds->pipes[pi].sub_tokens_size = cnt;
	else
	{
		//printf("subshell token error =%zu, tokens[i].type =%d, [i-1]=%d\n", cmds->pipes[pi].sub_tokens_size, tokens[i].type, tokens[i-1].type);
		cmds->pipes[pi].sub_tokens = NULL;
		cmds->pipes[pi].subshell_error = true;
	}
	//printf("subshell token end =%zu\n", cmds->pipes[pi].sub_tokens_size);
	return (i);
}

/*
   size_t	set_paren(t_token *tokens, t_cmds *cmds, size_t i, size_t pi)

   size_t	cnt;

   cnt = 0;
   cmds->pipes[pi].sub_tokens = &(tokens[++i]);
   cmds->has_subshell = true;
   cmds->pipes[pi].is_subshell = true;
   cmds->pipes[pi].subshell_error = false;
   while ((tokens[i].type != EOS && tokens[i].type != RPAREN) && ++i)
   cnt++;
   if (tokens[i].type == RPAREN && tokens[i - 1].type != LPAREN)
   cmds->pipes[pi].sub_tokens_size = cnt;
   else
   {
   cmds->pipes[pi].sub_tokens = NULL;
   cmds->pipes[pi].subshell_error = true;
   }
   printf("subshell token end =%zu\n", cmds->pipes[pi].sub_tokens_size);
   return (i);
   }
   */
