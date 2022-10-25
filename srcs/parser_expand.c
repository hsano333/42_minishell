/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:16 by hsano             #+#    #+#             */
/*   Updated: 2022/10/26 02:41:32 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parser.h"
#include "libft_str.h"
#include "minishell.h"
#include "lexer_util.h"
#include "parser_expand.h"

token_type	is_expand(t_token *token)
{
	if (token->type == SINGLE_QUOTE 
		|| token->type == DOUBLE_QUOTE
		|| (token->type & DOLLER) == DOLLER
		|| (token->type & ASTERISK) == ASTERISK)
		return (token->type);
	return (NON);
}

void	expand_quote(t_token *token, size_t end_no)
{
	size_t	i;
	size_t	len;
	char	*expanded_str;

	len = 0;
	i = 1;
	while (token[i].id != end_no)
	{
		len += ft_strlen(token[i].literal);
		token[i].valid = false;
		i++;
	}
	token[i].valid = false;
	if (len == 0)
	{
		//token[0].literal[0] = '\0';
		return ;
	}
	expanded_str = malloc(len + 1);
	ft_strlcpy(expanded_str, token[1].literal, len + 1);
	i = 2;
	while (token[i].id != end_no)
	{
		ft_strlcat(expanded_str, token[i].literal, len + 1);
		i++;
	}
	free(token[0].literal);
	token[0].literal = expanded_str;
	token[0].type = IDENT;
}

static void	expand_doller_asterisk(t_token *token, token_type pre_token)
{
	printf("expand_doller_asteriski No.1\n");
	expand_doller(token, pre_token);
	printf("expand_doller_asteriski No.2\n");
	expand_asterisk(token, pre_token);
	printf("expand_doller_asteriski No.2\n");
}

size_t	parser_expand(t_token *tokens, token_type pre_token, size_t i)
{
	size_t	end_no;
	token_type	cur_token;

	end_no = false;
	printf("parser_expand No.1\n");
	while (tokens[i].type != EOS && is_expand(&(tokens[i])) == NON)
		i++;
	printf("parser_expand No.2\n");
	cur_token = is_expand(&(tokens[i]));
	printf("parser_expand No.3\n");
	if (tokens[i].type == EOS)
		return (end_no);
	else if (DOLLER == (cur_token & DOLLER) || ASTERISK == (cur_token & ASTERISK))
		expand_doller_asterisk(&(tokens[i]), pre_token);
	else if (cur_token != NON && pre_token == NON)
		end_no = parser_expand(tokens, cur_token, i + 1);
	else if (cur_token == pre_token)
		return (tokens[i].id);
	printf("parser_expand No.4\n");
	if (end_no > tokens[i].id)
	{
	printf("parser_expand No.5\n");
		expand_quote(&(tokens[i]), end_no);
	printf("parser_expand No.6\n");
		i = end_no;
	}
	printf("parser_expand No.7\n");
	if (tokens[i].type != EOS)
		end_no = parser_expand(tokens, pre_token, i + 1);
	printf("parser_expand No.8\n");
	return (end_no);
}

/*
int	parser_expand(t_token *tokens)
{
	parser_expand(tokens, NON, 0);
	return (true);
}
*/
