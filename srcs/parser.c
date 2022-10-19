/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:06:43 by hsano             #+#    #+#             */
/*   Updated: 2022/10/19 15:43:15 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_expand.h"
#include "parser_std.h"
#include "parser_heredoc.h"

static size_t	count_comds(t_token *tokens)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (tokens[i].type != EOS)
	{
		if (!tokens[i].valid)
		{
			i++;
			continue ;
		}
		if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND)
			cnt++;
		i++;
	}
	return (cnt);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;
	size_t	cmds_num;

	cmds_num = count_comds(tokens);
	cmds = (t_cmd *)malloc(sizeof(t_cmd) * (cmds_num + 1));
	parser_expand(tokens);
	create_heredoc_file(tokens);
	search_std_in_and_out(tokens, cmds);
	cmds[cmds_num].last = true;
	//cmds[0].in = (int)(tokens[0].type);
	return (cmds);
}
