/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handling_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:31:19 by hsano             #+#    #+#             */
/*   Updated: 2022/11/17 21:54:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_handling_error.h"
#include "exit_status.h"
#include "token_parenthesis.h"
#include "token_type.h"
#include "lexer_quote_flag.h"

static void	check_lexer_memmory_error(t_token *tokens)
{
	int		err;
	size_t	i;

	err = false;
	i = 0;
	while (tokens[i].type != EOS)
	{
		if (tokens[i].literal == NULL)
		{
			err = true;
			break ;
		}
		i++;
	}
	if (err)
	{
		clear_tokens(tokens);
		kill_myprocess(12, NULL, tokens, NULL);
	}
}

static int	put_quote_error(t_token *tokens)
{
	if (tokens->type == EOS)
		ft_putendl_fd(\
			"minishell: syntax error near unexpected token `newline'", 2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tokens->literal, 2);
		ft_putendl_fd("'", 2);
	}
	set_exit_status(258);
	return (true);
}

static int	have_quote_error(t_token *tokens)
{
	size_t				i;

	i = 0;
	set_lexer_quote(NON);
	while (tokens[i].type != EOS)
	{
		if (get_lexer_quote() != NON)
			;
		else if (tokens[i].valid && is_token_must_next_string(tokens[i].type))
		{
			if (is_string_token(tokens[i + 1].type) == false)
			{
				put_quote_error(&(tokens[i + 1]));
				return (true);
			}
		}
		set_lexer_quote_util(tokens[i].type);
		i++;
	}
	return (false);
}

static int	begin_token_error(t_token *tokens)
{
	size_t	i;

	i = 0;
	set_lexer_quote(NON);
	while (tokens[i].type != EOS)
	{
		if (get_lexer_quote() != NON)
			;
		else if (i == 0 && is_begin_error_token(tokens[i].type))
		{
			printf("No.10\n");
			put_quote_error(&(tokens[i]));
			return (true);
		}
		else if (i > 0 && (tokens[i].type == PIPE || tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND))
		{
			if (is_begin_error_token(tokens[i + 1].type))
			{
			printf("No.11\n");
				put_quote_error(&(tokens[i]));
				return (true);
			}
		}
		set_lexer_quote_util(tokens[i].type);
		i++;
	}
	return (false);
}

t_token	*lexer_handling_error(t_token *tokens)
{
	int		error[3];

	check_lexer_memmory_error(tokens);
	error[0] = have_quote_error(tokens);
	error[1] = begin_token_error(tokens);
	error[2] = have_paren_error(tokens);
	if (error[0] || error[1] || error[2])
	{
		clear_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}
