/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 03:43:45 by hsano             #+#    #+#             */
/*   Updated: 2022/11/19 04:14:36 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_concat.h"
#include "parser_error.h"
#include "parser_util.h"
#include "libft_str.h"

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

int	parser_concat(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i].type != EOS)
	{
		if (tokens[i].valid && tokens[i].concat_back)
		{
			if (tokens[i + 1].valid)
				concat_str(tokens, i, i + 1);
			tokens[i + 1].valid = false;
		}
		else if (tokens[i].valid && tokens[i].concat_front)
		{
			if (i > 0 && tokens[i - 1].valid)
				concat_str(tokens, i - 1, i);
			tokens[i].valid = false;
		}
		if (get_parser_error())
			break ;
		i++;
	}
	return (true);
}
