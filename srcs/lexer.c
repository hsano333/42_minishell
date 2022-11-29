/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:20:00 by hsano             #+#    #+#             */
/*   Updated: 2022/11/30 03:01:45 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_util.h"
#include "libft_isto.h"
#include "kill_myprocess.h"
#include "lexer_quote_flag.h"
#include "lexer_handling_error.h"
#include "parser_heredoc.h"
#include "token_type.h"
#include "libft_str.h"

size_t	token_len(t_token_type *type, char *str, size_t i, size_t cnt)
{
	t_token_type	tmp_type;

	if (!(*type == IDENT || *type == DOLLER \
				|| *type == ASTERISK || *type == EXIT_STATUS))
		return (token_len_helper(*type));
	i = 0;
	cnt = 1;
	while (str[++i])
	{
		if ((ft_isspace(*str) && (get_lexer_quote() == NON)) || *type == EOS)
			break ;
		tmp_type = identify_token(str[i], str[i + 1]);
		if (tmp_type == IDENT || tmp_type == DOLLER \
				|| tmp_type == ASTERISK || tmp_type == EXIT_STATUS)
		{
			if (tmp_type == EXIT_STATUS && ++i)
				cnt += 2;
			else
				cnt++;
			*type = (*type | tmp_type);
		}
		else
			break ;
	}
	return (cnt);
}

void	lexer_set_token(t_token *tokens, t_token_type type, char *str, size_t i)
{
	tokens[i].len = token_len(&type, str, 0, 1);
	if (type == EOS)
		tokens[i].type = type;
	else if (type == WHITE_SPACE && get_lexer_quote() != NON)
		tokens[i].type = IDENT;
	else if (get_lexer_quote() == SINGLE_QUOTE && type != SINGLE_QUOTE)
		tokens[i].type = IDENT;
	else
		tokens[i].type = type;
	type = tokens[i].type;
	if (get_lexer_quote() == type && !ft_isspace(str[1]) && str[1] != '\0' \
		&& is_string_token(identify_token(str[1], str[2])) \
		&& is_quote_token(type))
		tokens[i + 1].concat_front = true;
	if (i > 0 && is_quote_token(type) && !ft_isspace(str[-1]) \
		&& get_lexer_quote() == NON)
		tokens[i - 1].concat_back = true;
	if (i > 0 && is_token_must_next_string(type) && !ft_isspace(str[-1]) \
		&& get_lexer_quote() == NON && (tokens[i - 1].type) == IDENT)
		tokens[i].flag_redir = true;
	set_lexer_quote_util(type);
	tokens[i].literal = ft_substr(str, 0, tokens[i].len);
	if ((type == LT || type == D_LT) && get_lexer_quote() == NON)
		tokens[i].option_fd = 1;
}

static void	set_option_fd(t_token *tokens)
{
	size_t	i;
	int		type;
	int		error;

	i = 0;
	while (tokens[i].type != EOS)
	{
		type = tokens[i].type;
		if (i > 0 && is_token_must_next_string(type))
		{
			if (tokens[i].flag_redir && tokens[i - 1].type == IDENT \
					&& ft_isdigitstr(tokens[i - 1].literal))
			{
				tokens[i].option_fd = ft_atoi(tokens[i - 1].literal, &error);
				tokens[i - 1].valid = false;
			}
		}
		i++;
	}
}

static t_token	*analyze_str(char *str, t_token *tokens, size_t i)
{
	size_t	k;
	int		paren_flag_cnt;

	k = 0;
	paren_flag_cnt = 0;
	while (str[k])
	{
		if (ft_isspace(str[k]) && (get_lexer_quote() == NON) && k++)
			continue ;
		lexer_set_token(tokens, identify_token(str[k], str[k + 1]) \
								, &(str[k]), i);
		if (paren_flag_cnt > 0)
			tokens[i].valid = false;
		if (tokens[i].type == LPAREN)
			paren_flag_cnt++;
		else if (tokens[i].type == RPAREN)
			paren_flag_cnt--;
		if (paren_flag_cnt == 0 && tokens[i].type == RPAREN)
			tokens[i].valid = true;
		k += tokens[i++].len;
	}
	lexer_set_token(tokens, EOS, "", i);
	if (get_lexer_quote() != NON && change_quote_type(tokens, &(i), &k, str))
		tokens = analyze_str(&str[k], tokens, i);
	return (tokens);
}

t_token	*lexer(char *str)
{
	size_t	len;
	t_token	*tokens;
	size_t	i;

	set_lexer_quote(NON);
	len = ft_strlen(str);
	tokens = (t_token *)malloc(sizeof(t_token) * (len + 1));
	if (!tokens)
		lexer_memory_error(tokens);
	ft_memset(tokens, 0, sizeof(t_token) * (len + 1));
	i = 0;
	while (i < len)
	{
		tokens[i].id = i;
		tokens[i++].valid = true;
	}
	tokens = analyze_str(str, tokens, 0);
	set_option_fd(tokens);
	if (create_heredoc_file(tokens) == false)
	{
		clear_tokens(tokens);
		return (NULL);
	}
	return (lexer_handling_error(tokens));
}
