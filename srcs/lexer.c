/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:20:00 by hsano             #+#    #+#             */
/*   Updated: 2022/10/31 04:10:36 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_util.h"
#include "libft_isto.h"
#include "kill_myprocess.h"
#include "lexer_quote_flag.h"


size_t	token_len(token_type *type, char *str)
{
	size_t	i;
	size_t	cnt;
	token_type	tmp_type;

	if (!(*type == IDENT || *type == DOLLER || *type == ASTERISK || *type == EXIT_STATUS))
		return (token_len_helper(*type));
	i = 0;
	cnt = 1;
	while (str[++i])
	{
		if (ft_isspace(*str) && (get_lexer_quote() == NON))
			break ;
		tmp_type = identify_token(str[i], str[i + 1]);
		if (tmp_type == IDENT || tmp_type == DOLLER || tmp_type == ASTERISK || tmp_type == EXIT_STATUS)
		{
			if (tmp_type == EXIT_STATUS)
			{
				cnt += 2;
				i++;
			}
			else
				cnt++;
			*type= (*type | tmp_type);
		}
		else
			break ;
	}
	return (cnt);
}

static void	set_token(t_token *token, token_type type, char *str, size_t id)
{
	token->id = id;
	token->valid = true;
	token->expand = false;
	token->error = false;
	token->len = token_len(&type, str);
	if (type == WHITE_SPACE && get_lexer_quote() != NON)
		token->type = IDENT;
	else
		token->type = type;
	token->literal = ft_substr(str, 0, token->len);
	if (get_lexer_quote() == type)
		set_lexer_quote(NON);
	else if (type == DOUBLE_QUOTE || type == SINGLE_QUOTE)
		set_lexer_quote(type);
}

t_token	*lexer(char *str)
{
	size_t	i;
	size_t	len;
	t_token	*tokens;
	
	len = ft_strlen(str);
	i = 0;
	tokens = (t_token *)malloc(sizeof(t_token) * (len + 1));
	if (!tokens)
		kill_myprocess(12, NULL, NULL, NULL);
	i = 0;
	while (*str)
	{
		if (ft_isspace(*str) && (get_lexer_quote() == NON) && str++)
			continue ;
		set_token(&(tokens[i]), identify_token(*str, str[1]), str, i);
		str += tokens[i++].len;
	}
	set_token(&(tokens[i]), EOS, "", i);
	check_lexer_error(tokens);
	return (tokens);
}
