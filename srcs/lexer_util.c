/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:54:44 by hsano             #+#    #+#             */
/*   Updated: 2022/10/31 04:04:14 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_util.h"
//#include "lexer.h"
# include "kill_myprocess.h"

static token_type	identify_token_partial(char c, char next_c)
{
	if (c == '|' && next_c == '|')
		return (D_PIPE);
	else if (c == '|')
		return (PIPE);
	else if (c == '&' && next_c == '&')
		return (D_AMPERSAND);
	else if (c == '>' && next_c == '>')
		return (D_LT);
	else if (c == '>')
		return (LT);
	else if (c == '<' && next_c == '>')
		return (GLT);
	else if (c == '<' && next_c == '<')
		return (D_GT);
	else if (c == '<')
		return (GT);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	return (NON);
}

token_type	identify_token(char c, char next_c)
{
	token_type	type;

	type = identify_token_partial(c, next_c);
	if (type != NON)
		return (type);
	//if (c == '.' && next_c == '.')
		//return (D_DOT);
	//else if (c == '.')
		//return (DOT);
	//else if (c == ';')
		//return (SEMICOLON);
	//else if (c == '=')
		//return (EQUAL);
	if (c == '*')
		return (ASTERISK);
	else if (c == '$' && next_c == '\?')
		return (EXIT_STATUS);
	else if (c == '$')
		return (DOLLER);
	else if (c == '\0')
		return (EOS);
	else if (ft_isspace(c))
		return (WHITE_SPACE);
	return (IDENT);
}


/*
size_t	whitespace_len(char *str)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			cnt++;
		i++;
	}
	return (cnt);
}
*/

size_t token_len_helper(token_type type)
{
	if (type == D_PIPE || type == D_AMPERSAND || type == D_LT \
			|| type == D_GT || type == GLT || type == EXIT_STATUS)
		return (2);
	return (1);
}

t_token	*check_lexer_error(t_token *tokens)
{
	int	err;
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
		kill_myprocess(12, NULL, tokens, NULL);
	return (tokens);
}

void	clear_tokens(t_token *tokens)
{
	size_t	i;
	
	i = 0;
	while (tokens[i].type != EOS)
	{
		free(tokens[i].literal);
		tokens[i].literal = NULL;
		i++;
	}
	free(tokens[i].literal);
	tokens[i].literal = NULL;
	free(tokens);
	tokens = NULL;
}

void	put_tokens(t_token *tokens)
{
	size_t	i;
	t_token	*tmp_token;
	
	i = 0;
	while (tokens[i].type != EOS)
	{
		tmp_token = &(tokens[i]);
		if (tmp_token->valid)
			printf("id=%zu,type=%d, len=%zu str=[%s], valid=%d\n ", tmp_token->id, tmp_token->type, tmp_token->len, tmp_token->literal, tmp_token->valid);
		i++;
	}
}
