/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:59:16 by hsano             #+#    #+#             */
/*   Updated: 2022/11/17 21:15:12 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parenthesis.h"
#include "lexer_quote_flag.h"
#include "lexer.h"
#include "lexer_util.h"
#include "parser.h"
#include "libft_put.h"
#include "token_type.h"
#define E_MSG "minishell:syntax error near unexpected token `)'\n"

static int	is_invalid_near_token(t_token *tokens, size_t i)
{
	if (tokens[i].type == LPAREN)
	{
		if (i > 0 && !is_connection_token(tokens[i - 1].type))
		{
			printf("No.1\n");
			return (true);
		}
		else if (is_begin_error_token(tokens[i + 1].type))
		{
			printf("No.2\n");
			return (true);
		}
	}
	else if (tokens[i].type == RPAREN)
	{
		if (i > 0 && !is_string_token(tokens[i - 1].type))
		{
			printf("No.3\n");
			return (true);
		}
		else if (is_string_token(tokens[i + 1].type))
		{
			printf("No.4\n");
			return (true);
		}
	}
	return (false);
}

static int	check_closed(t_token *tokens, size_t *i, int *error)
{
	int	cnt;

	cnt = 1;
	if (is_invalid_near_token(tokens, *i))
		*error = true;
	//if (*i > 0 && (tokens[*i - 1].type != PIPE && tokens[*i - 1].type != D_PIPE && tokens[*i - 1].type != D_AMPERSAND) && tokens[*i - 1].type != LPAREN)
		//*error = true;
	while (tokens[++(*i)].type != EOS)
	{
		if (get_lexer_quote() == NON && tokens[*i].type == RPAREN)
		{
			cnt--;
			////if ((tokens[*i + 1].type == SINGLE_QUOTE) || (tokens[*i + 1].type == DOUBLE_QUOTE))
				//*error = true;
			if (is_invalid_near_token(tokens, *i))
				*error = true;
			if (cnt == 0)
				return (true);
		}
		else if (get_lexer_quote() == NON && tokens[*i].type == LPAREN)
			cnt++;
		set_lexer_quote_util(tokens[*i].type);
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
		set_lexer_quote_util(tokens[i++].type);
		if (error)
			ft_putstr_fd(E_MSG, 2);
		if (!closed || error)
			return (true);
	}
	return (false);
}

int	enable_paren_token(t_pipe *pipe)
{
	//size_t	k;
	size_t	j;
	int	cnt;

	if (!pipe->sub_tokens)
		return (true);
	//k = 0;
	cnt = 0;
	//while (k < cmds->len)
	{
		j = 0;
		while (j < pipe->sub_tokens_size)
		{
			//if (cnt == 0 && !pipe->sub_tokens[j].subshell_invalid )
			if (cnt == 0)
			{
				//printf("revalid\n");
				pipe->sub_tokens[j].valid = true;
			}
			if (pipe->sub_tokens[j].type == LPAREN)
				cnt++;
			else if (pipe->sub_tokens[j].type == RPAREN)
			{
				cnt--;
				if (cnt == 0)
					pipe->sub_tokens[j].valid = true;
			}
			j++;
		}
		//k++;
	}
	return (true);
}

size_t	set_paren(t_token *tokens, t_cmds *cmds, size_t i, size_t pi)
{
	size_t	cnt;
	size_t	token_cnt;

	cnt = 1;
	token_cnt = 0;
	cmds->pipes[pi].sub_tokens = &(tokens[++i]);
	cmds->has_subshell = true;
	cmds->pipes[pi].is_subshell = true;
	cmds->pipes[pi].subshell_error = false;
	while (tokens[i].type != EOS && ++token_cnt)
	{
		if (tokens[i].type == LPAREN)
			cnt++;
		if (tokens[i].type == RPAREN && cnt--)
			if (cnt == 0 && token_cnt--)
				break;
		//if (!tokens[i].valid)
		//	tokens[i].subshell_invalid = true;
		//tokens[i].valid = false;
		i++;
	}
	cmds->pipes[pi].sub_tokens_size = token_cnt;
	if (tokens[i].type == EOS && i--)
		cmds->pipes[pi].sub_tokens = NULL;
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
