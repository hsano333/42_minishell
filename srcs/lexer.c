/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:20:00 by hsano             #+#    #+#             */
/*   Updated: 2022/11/11 01:28:14 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_util.h"
#include "libft_isto.h"
#include "kill_myprocess.h"
#include "lexer_quote_flag.h"
#include "lexer_handling_error.h"

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
		if (ft_isspace(*str) && (get_lexer_quote() == NON))
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

static void	set_token(t_token *tokens, t_token_type type, char *str, size_t i)
{
	tokens[i].id = i;
	tokens[i].valid = true;
	tokens[i].len = token_len(&type, str, 0, 1);
	if (type == EOS)
		tokens[i].type = type;
	else if (type == WHITE_SPACE && get_lexer_quote() != NON)
		tokens[i].type = IDENT;
	else if (get_lexer_quote() == SINGLE_QUOTE && type != SINGLE_QUOTE)
		tokens[i].type = IDENT;
	else
		tokens[i].type = type;
	if ((tokens[i].type == SINGLE_QUOTE || tokens[i].type == DOUBLE_QUOTE) \
										&& i > 0 && !ft_isspace(str[-1]))
		tokens[i - 1].concat_back = true;
	if ((tokens[i].type == SINGLE_QUOTE || tokens[i].type == DOUBLE_QUOTE) \
										&& type != EOS && !ft_isspace(str[1]))
		tokens[i + 1].concat_front = true;
	set_lexer_quote_util(type);
	tokens[i].literal = ft_substr(str, 0, tokens[i].len);
	if (type == LT || type == D_LT)
		tokens[i].option_fd = 1;
}

static void	set_option_fd(t_token *tokens)
{
	size_t	i;
	int		type;

	i = 0;
	while (tokens[i].type != EOS)
	{
		type = tokens[i].type;
		if (i > 0 && (type == GLT || type == GT || type == LT \
				|| type == D_GT || type == D_LT))
		{
			if (tokens[i - 1].type == IDENT && tokens[i - 1].len == 1 \
					&& ft_isdigit(tokens[i - 1].literal[0]))
			{
				tokens[i].option_fd = tokens[i - 1].literal[0] - 0x30;
				tokens[i - 1].valid = false;
			}
		}
		i++;
	}
}

static t_token	*analyze_str(char *str, t_token *tokens, size_t i)
{
	char	*str_bk;
	size_t	k;

	str_bk = str;
	k = 0;
	while (str[k])
	{
		if (ft_isspace(str[k]) && (get_lexer_quote() == NON) && k++)
			continue ;
		set_token(tokens, identify_token(str[k], str[k + 1]), &(str[k]), i);
		k += tokens[i].len;
		i++;
	}
	set_token(tokens, EOS, "", i);
	if (get_lexer_quote() != NON && change_quote_type(tokens, &(i), &k))
		tokens = analyze_str(&str[k], tokens, i);
	return (tokens);
}

t_token	*lexer(char *str)
{
	size_t	len;
	t_token	*tokens;

	set_lexer_quote(NON);
	len = ft_strlen(str);
	tokens = (t_token *)malloc(sizeof(t_token) * (len + 1));
	if (!tokens)
		kill_myprocess(12, NULL, NULL, NULL);
	ft_memset(tokens, 0, sizeof(t_token) * (len + 1));
	tokens = analyze_str(str, tokens, 0);
	set_option_fd(tokens);
	return (lexer_handling_error(tokens));
}
