/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:16 by hsano             #+#    #+#             */
/*   Updated: 2022/11/17 22:40:27 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parser.h"
#include "libft_str.h"
#include "minishell.h"
#include "lexer_util.h"
#include "parser_expand.h"
#include "kill_myprocess.h"
#include "parser_error.h"

static t_token_type	is_expand(t_token *token)
{
	if (token->valid && (token->type == SINGLE_QUOTE \
		|| token->type == DOUBLE_QUOTE \
		|| (token->type & DOLLER) == DOLLER \
		|| (token->type & ASTERISK) == ASTERISK \
		|| (token->type & EXIT_STATUS) == EXIT_STATUS))
		return (token->type);
	return (NON);
}

int	expand_quote(t_token *token, size_t end_no)
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
		return (true);
	expanded_str = malloc(len + 1);
	if (!expanded_str)
		set_parser_error(true);
	ft_strlcpy(expanded_str, token[1].literal, len + 1);
	i = 2;
	while (token[i].id != end_no && ++i)
		ft_strlcat(expanded_str, token[i - 1].literal, len + 1);
	free(token[0].literal);
	token[0].literal = expanded_str;
	token[0].type = IDENT;
	return (true);
}

static void	expand_doller_asterisk(t_token *tokens \
		, t_token_type pre_token, size_t i)
{
	t_token	*token;

	token = (t_token *)(&tokens[i]);
	if (!expand_exit_status(token))
		set_parser_error(true);
		//kill_myprocess(12, NULL, tokens, NULL);
	if (!expand_doller(token, pre_token))
		set_parser_error(true);
		//kill_myprocess(12, NULL, tokens, NULL);
	if (!expand_asterisk(token, pre_token))
		set_parser_error(true);
		//kill_myprocess(12, NULL, tokens, NULL);
}

size_t	parser_expand(t_token *tokens, t_token_type pre_token, size_t i)
{
	size_t			end_no;
	t_token_type	cur_token;

	end_no = 0;
	//printf("paraser No.1 i=%zu, type=%d\n", i, tokens[i].type);
	while (tokens[i].type != EOS && is_expand(&(tokens[i])) == NON)
	{
	//printf("paraser No.2 i=%zu, type=%d\n", i, tokens[i].type);
		i++;
	}
	//printf("paraser No.3 i=%zu, type=%d\n", i, tokens[i].type);
	cur_token = is_expand(&(tokens[i]));
	//printf("paraser No.4 i=%zu, type=%d\n", i, tokens[i].type);
	if (tokens[i].type == EOS)
		return (end_no);
	else if (DOLLER == (cur_token & DOLLER) \
			|| ASTERISK == (cur_token & ASTERISK) \
			|| EXIT_STATUS == (cur_token & EXIT_STATUS))
		expand_doller_asterisk(tokens, pre_token, i);
	else if (cur_token != NON && pre_token == NON)
		end_no = parser_expand(tokens, cur_token, i + 1);
	else if (cur_token != IDENT && pre_token == IDENT)
		end_no = parser_expand(tokens, cur_token, i + 1);
	else if (cur_token == pre_token)
		return (tokens[i].id);
	//printf("paraser No.5 i=%zu, type=%d\n", i, tokens[i].type);
	if (end_no > tokens[i].id && expand_quote(&(tokens[i]), end_no))
		i = end_no;
	//printf("paraser No.6 i=%zu, type=%d\n", i, tokens[i].type);
	if (tokens[i].type != EOS)
		end_no = parser_expand(tokens, pre_token, i + 1);
	//printf("paraser No.7 i=%zu, type=%d\n", i, tokens[i].type);
	return (end_no);
}
