/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:59:16 by hsano             #+#    #+#             */
/*   Updated: 2022/11/16 12:02:02 by hsano            ###   ########.fr       */
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
	if (*i > 0 && (tokens[*i - 1].type != PIPE && tokens[*i - 1].type != D_PIPE && tokens[*i - 1].type != D_AMPERSAND) && tokens[*i - 1].type != LPAREN)
			*error = true;
	while (tokens[*i].type != EOS)
	{
		if (tokens[*i].type == RPAREN)
		{
			if ((tokens[*i + 1].type == SINGLE_QUOTE) || (tokens[*i + 1].type == DOUBLE_QUOTE))
				*error = true;
			return (true);
		}
		(*i)++;
	}
	ft_putstr_fd("minishell:not closed parenthesis\n", 2);
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
	set_lexer_quote(NON);
	while (tokens[i].type != EOS)
	{
		if (get_lexer_quote() == NON && tokens[i].type == LPAREN)
			closed = check_closed(tokens, &i, &error);
		else if (get_lexer_quote() == NON && tokens[i].type == RPAREN)
			error = true;
		set_lexer_quote_util(tokens[i++].type);
		if (error)
			ft_putstr_fd(E_MSG, 2);
		if (!closed || error)
			return (true);
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
	//printf("cmds->len=%zu\n", cmds->len);
	while (k < cmds->len)
	{
		//printf("cmds->pipes[%zu].sub_tokens_size=%zu\n", k,cmds->pipes[k].sub_tokens_size);
		j = 0;
		while (j < cmds->pipes[k].sub_tokens_size)
		{
			//printf("envale sub token k=%zu, j=%zu, str=%s\n", k, j, cmds->pipes[k].sub_tokens[j].literal);
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
