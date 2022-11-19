/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 03:43:45 by hsano             #+#    #+#             */
/*   Updated: 2022/11/19 19:42:24 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_concat.h"
#include "parser_error.h"
#include "parser_util.h"
#include "libft_str.h"
#include "token_type.h"

static size_t	concat_str(t_token *tokens, size_t i, size_t j)
{
	char	*tmp;

	if (j == 0 || get_parser_error())
		return (0);
	tmp = ft_strjoin(tokens[i].literal, tokens[j].literal);
	if (!tmp)
		set_parser_error(true);
	free(tokens[i].literal);
	tokens[i].literal = tmp;
	return (i);
}

static size_t	concat_front(t_token *tokens, size_t i)
{
	size_t	bk;

	bk = i;
	while (i > 0 && tokens[--i].type != EOS)
	{
		if (tokens[i].valid)
			break ;
	}
	if (tokens[i].valid)
		concat_str(tokens, i, bk);
	tokens[bk].valid = false;
	i = bk;
	return (i);
}

static size_t	concat_back(t_token *tokens, size_t i)
{
	size_t	bk;

	bk = i;
	while (tokens[++i].type != EOS)
	{
		if (tokens[i].valid)
			break ;
	}
	if (tokens[i].valid && tokens[i].type != EOS)
		concat_str(tokens, bk, i);
	tokens[i].valid = false;
	return (bk);
}

int	parser_concat(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i].type != EOS)
	{
		if (tokens[i].valid && tokens[i].concat_back)
		{
			if (&tokens[i + 1])
				parser_concat(&(tokens[i + 1]));
			i = concat_back(tokens, i);
		}
		if (i > 0 && tokens[i].valid && tokens[i].concat_front)
			i = concat_front(tokens, i);
		if (get_parser_error() || tokens[i].type == EOS)
			break ;
		i++;
	}
	return (true);
}
