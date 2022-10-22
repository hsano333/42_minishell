/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:20:00 by hsano             #+#    #+#             */
/*   Updated: 2022/10/22 13:49:28 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_util.h"

token_type	identify_token_partial(char c, char next_c)
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
	else if (c == '$')
		return (DOLLER);
	else if (c == '$' && next_c == '\?')
		return (EXIT_STATUS);
	else if (c == '\0')
		return (EOS);
	return (IDENT);
}

size_t	token_len(token_type *type, char *str)
{
	size_t	i;
	size_t	cnt;
	token_type	tmp_type;

	if (!(*type == IDENT || *type == DOLLER || *type == ASTERISK))
		return (token_len_helper(*type));
	i = 0;
	cnt = 1;
	while (str[++i])
	{
		if (is_whitespace(str[i]))
			break ;
		tmp_type = identify_token(str[i], str[i + 1]);
		if (tmp_type == IDENT || tmp_type == DOLLER || tmp_type == ASTERISK)
		{
			cnt++;
			//if (tmp_type == DOLLER || tmp_type == ASTERISK)
			*type= (*type | tmp_type);
		}
		else
			break ;
	}
	return (cnt);
}

static void	set_token(t_token *token, token_type type, char *str, size_t id)
{
	token->len = token_len(&type, str);
	token->type = type;
	token->literal = ft_substr(str, 0, token->len);
	token->id = id;
	token->valid = true;
}

t_token	*lexer(char *str)
{
	size_t	i;
	size_t	len;
	t_token	*tokens;
	
	len = ft_strlen(str) - whitespace_len(str);
	tokens = (t_token *)malloc(sizeof(t_token) * (len + 1));
	i = 0;
	while (*str)
	{
		if (is_whitespace(*str))
		{
			str++;
			continue ;
		}
		set_token(&(tokens[i]), identify_token(*str, str[1]), str, i);
		str += tokens[i].len;
		i++;
	}
	set_token(&(tokens[i]), EOS, "", i);
	return (check_error(tokens));
}
