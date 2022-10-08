/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:54:44 by hsano             #+#    #+#             */
/*   Updated: 2022/10/09 02:41:49 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_util.h"

int	is_whitespace(char c)
{
	if (c == ' ' || (0x09 <= c && c <= 0x0D))
		return (true);
	return (false);
}

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

size_t token_len_helper(token_type type)
{
	if (type == D_PIPE || type == D_AMPERSAND || type == D_LT \
			|| type == D_GT || type == D_DOT || type == EXIT_STATUS)
		return (2);
	return (1);
}
