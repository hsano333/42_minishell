/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:59:16 by hsano             #+#    #+#             */
/*   Updated: 2022/11/30 01:53:50 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_parenthesis.h"
#include "lexer_quote_flag.h"
#include "lexer.h"
#include "lexer_util.h"
#include "exit_status.h"
#include "parser.h"
#include "libft_put.h"
#include "token_type.h"
#define E_MSG "minishell:syntax error near unexpected token `)'\n"

static int	is_invalid_near_token(t_token *tokens, size_t i)
{
	if (tokens[i].valid && tokens[i].type == LPAREN)
	{
		if (i > 0 && tokens[i - 1].valid \
				&& !is_connection_token(tokens[i - 1].type))
			return (true);
		else if (tokens[i + 1].valid \
				&& is_begin_error_token(tokens[i + 1].type))
			return (true);
	}
	else if (tokens[i].valid && tokens[i].type == RPAREN)
	{
		if (i > 0 && tokens[i - 1].valid \
				&& !is_rparen_left_valid_token(tokens[i - 1].type))
			return (true);
		else if (tokens[i + 1].valid && is_string_token(tokens[i + 1].type))
			return (true);
	}
	return (false);
}

static int	check_closed(t_token *tokens, size_t *i, int *error)
{
	int	cnt;

	cnt = 1;
	if (is_invalid_near_token(tokens, *i))
		*error = true;
	while (tokens[++(*i)].type != EOS)
	{
		if (get_lexer_quote() == NON && tokens[*i].type == RPAREN)
		{
			cnt--;
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
	size_t	i;
	int		closed;
	int		error;

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
		{
			set_exit_status(258);
			ft_putstr_fd(E_MSG, 2);
		}
		if (!closed || error)
			return (true);
	}
	return (false);
}

int	enable_paren_token(t_pipe *pipe)
{
	size_t	j;
	int		cnt;

	if (!pipe->sub_tokens)
		return (true);
	cnt = 0;
	j = 0;
	while (j < pipe->sub_tokens_size)
	{
		if (cnt == 0)
			pipe->sub_tokens[j].valid = true;
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
				break ;
		i++;
	}
	cmds->pipes[pi].sub_tokens_size = token_cnt;
	if (tokens[i].type == EOS && i--)
		cmds->pipes[pi].sub_tokens = NULL;
	return (i);
}
