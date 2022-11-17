/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:15:59 by hsano             #+#    #+#             */
/*   Updated: 2022/11/18 01:39:44 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_type.h"
#include "lexer.h"

int	is_token_must_next_string(t_token_type type)
{
	const t_token_type	tokens[] = {GLT, GT, LT, D_GT, D_LT};
	size_t				i;
	size_t				len;

	i = 0;
	len = sizeof(tokens) / sizeof(t_token_type);
	while (i < len)
	{
		if (type == tokens[i])
			return (true);
		i++;
	}
	return (false);
}

int	is_string_token(t_token_type type)
{
	const t_token_type	tokens[] = {IDENT, SINGLE_QUOTE, DOUBLE_QUOTE \
		, DOLLER, ASTERISK, EXIT_STATUS};
	size_t				i;
	size_t				len;

	i = 0;
	len = sizeof(tokens) / sizeof(t_token_type);
	while (i < len)
	{
		if (i <= 2 && tokens[i] == type)
			return (true);
		else if (i > 2 && tokens[i] == (type & tokens[i]))
			return (true);
		i++;
	}
	return (false);
}

int	is_connection_token(t_token_type type)
{
	const t_token_type	tokens[] = {PIPE, D_PIPE, D_AMPERSAND};
	size_t				i;
	size_t				len;

	i = 0;
	len = sizeof(tokens) / sizeof(t_token_type);
	while (i < len)
	{
		if (tokens[i] == (tokens[i] & type))
			return (true);
		i++;
	}
	return (false);
}
