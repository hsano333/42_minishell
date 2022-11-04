/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handling_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:31:19 by hsano             #+#    #+#             */
/*   Updated: 2022/11/05 04:03:14 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_handling_error.h"
#include "exit_status.h"

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
	size_t				j;
	const t_token_type	error_token[] = \
		{PIPE, D_PIPE, D_AMPERSAND, GLT, GT, LT, D_GT, D_LT, EOS};

	i = 0;
	while (tokens[i].type != EOS)
	{
		if ((tokens[i].type == GLT \
			|| tokens[i].type == GT || tokens[i].type == D_GT \
			|| tokens[i].type == LT || tokens[i].type == D_LT))
		{
			j = 0;
			while (1)
			{
				if (tokens[i + 1].type == error_token[j] \
						&& put_quote_error(&(tokens[i + 1])))
					return (true);
				if (error_token[j++] == EOS)
					break ;
			}
		}
		i++;
	}
	return (false);
}

static int	begin_token_error(t_token *tokens)
{
	size_t				j;
	size_t				len;
	const t_token_type	error_token[] = {PIPE, D_PIPE, D_AMPERSAND};

	len = sizeof(error_token) / sizeof(t_token_type);
	j = 0;
	while (j < len)
	{
		if (tokens[0].type == error_token[j])
		{
			put_quote_error(&(tokens[0]));
			return (true);
		}
		j++;
	}
	return (false);
}

t_token	*lexer_handling_error(t_token *tokens)
{
	int	error[2];

	check_lexer_memmory_error(tokens);
	error[0] = have_quote_error(tokens);
	error[1] = begin_token_error(tokens);
	if (error[0] || error[1])
	{
		clear_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}
