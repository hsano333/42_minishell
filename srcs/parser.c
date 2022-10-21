/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:06:43 by hsano             #+#    #+#             */
/*   Updated: 2022/10/22 02:04:13 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_init.h"
#include "parser_expand.h"
#include "parser_std.h"
#include "parser_heredoc.h"


t_cmds	*parser(t_token *tokens)
{
	t_cmds	*cmds;
	//size_t	cmds_num;

	cmds = init_parser(tokens);
	if (!cmds)
		return (NULL);
	parser_expand(tokens);
	create_heredoc_file(tokens);
	search_std_in_and_out(tokens, cmds);

	//cmds_num = count_comds(tokens);
	//////////cmds = (t_cmd *)malloc(sizeof(t_cmd) * (cmds_num + 1));
	//parser_expand(tokens);
	//create_heredoc_file(tokens);
	//search_std_in_and_out(tokens, cmds);
	//cmds[cmds_num].last = true;
	//cmds[0].in = (int)(tokens[0].type);
	return (cmds);
}
