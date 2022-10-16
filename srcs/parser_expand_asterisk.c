/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_asterisk.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:16 by hsano             #+#    #+#             */
/*   Updated: 2022/10/14 16:50:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parser.h"
#include "libft_str.h"
#include "minishell.h"
#include "lexer_util.h"

size_t	expand_asterisk(t_token *tokens, token_type pre_token)
{
	size_t	i;

	i = 0;
	while (tokens[i].type != EOS)
	{
		if (tokens[i].valid && tokens[i].type == ASTERISK)
		{
			printf("test i=%zu, pre=%d\n", i, pre_token);
			//search_word();
		}
		i++;
	}
	return (i);
}
