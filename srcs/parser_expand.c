/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:16 by hsano             #+#    #+#             */
/*   Updated: 2022/10/13 15:55:18 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft_str.h"
#include "minishell.h"
#include "lexer_util.h"

token_type	is_expand(t_token *token)
{
	if (token->type == SINGLE_QUOTE 
		|| token->type == DOUBLE_QUOTE
		|| token->type == DOLLER)
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
}

void	expand_doller(t_token *token, token_type pre_token)
{
	char	*str;

	if (pre_token == SINGLE_QUOTE)
		return ;
	str = get_env_val(&(token->literal[1]));
	//if (!str)
		//kill_process();
	free(token->literal);
	token->literal = str;
}

size_t	expand_str(t_token *tokens, token_type pre_token, size_t i)
{
	size_t	end_no;
	token_type	cur_token;

	end_no = false;
	while (tokens[i].type != EOS && is_expand(&(tokens[i])) == NON)
		i++;
	cur_token = is_expand(&(tokens[i]));
	if (tokens[i].type == EOS && pre_token != NON)
		return (end_no);
	else if (tokens[i].type == EOS && pre_token == NON)
		return (end_no);
	else if (cur_token == DOLLER)
		expand_doller(&(tokens[i]), pre_token);
	else if (cur_token != NON && pre_token == NON)
		end_no = expand_str(tokens, cur_token, i + 1);
	else if (cur_token == pre_token)
		return (tokens[i].id);
	if (end_no > tokens[i].id)
	{
		expand_quote(&(tokens[i]), end_no);
		i = end_no;
	}
	if (tokens[i].type != EOS)
		end_no = expand_str(tokens, pre_token, i + 1);
	return (end_no);
}
