/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:20:00 by hsano             #+#    #+#             */
/*   Updated: 2022/10/13 16:54:18 by hsano            ###   ########.fr       */
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

size_t	token_len(token_type type, char *str)
{
	size_t	i;
	size_t	cnt;

	if (!(type == IDENT || type == DOLLER || type == ASTERISK))
		return (token_len_helper(type));
	i = 1;
	cnt = 1;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			break ;
		if (identify_token(str[i], str[i + 1]) == IDENT)
			cnt++;
		else
			break ;
		i++;
	}
	return (cnt);
}

//t_token	*init_token(t_token *token, token_type type, char *str, size_t id)
void	init_token(t_token *token, token_type type, char *str, size_t id)
{
	//t_token	*token;

	//token = (t_token *)malloc(sizeof(t_token));
	//if (!token)
		//return (NULL);
	token->type = type;
	token->len = token_len(type, str);
	token->literal = ft_substr(str, 0, token->len);
	token->id = id;
	token->valid = true;
	//return (token);
}

t_token	*lexer(char *str)
{
	size_t	i;
	size_t	len;
	t_token	*tokens;
	//t_token	*tmp_token;
	
	len = ft_strlen(str) - whitespace_len(str);
	tokens = (t_token *)malloc(sizeof(t_token) * len);
	i = 0;
	while (*str)
	{
		if (is_whitespace(*str))
		{
			str++;
			printf("white space\n");
			continue ;
		}
		init_token(&(tokens[i]), identify_token(*str, str[1]), str, i);
		str += tokens[i].len;
		//tokens[i].type = identify_token(*str, str[1]);
		//tokens[i].literal = ft_strdup(str);
		//tokens[i].len = token_len(tokens[i].type, str);
		//tokens[i].id = i;
		//tokens[i].valid = true;
		//push_back(tokens, tmp_token);
		//str += tmp_token->len;
		//printf("No.1 str=%s,tokens[%zu].len=%zu \n", str, i,tokens[i].len);
		i++;
	}
	init_token(&(tokens[i]), EOS, "", i);
	return (check_error(tokens));
}
