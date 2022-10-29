/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:06:43 by hsano             #+#    #+#             */
/*   Updated: 2022/10/29 15:08:35 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_init.h"
#include "parser_expand.h"
#include "parser_std.h"
#include "parser_heredoc.h"
#include "stdio.h"
#include "parser_find_cmds.h"
#include "kill_myprocess.h"

void	print_comds(t_cmds *cmds)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (cmds)
	{
		printf("\ni=%zu, id=%zu, len=%zu, operator=%d, last=%d\n", i, cmds[i].id, cmds[i].len, cmds[i].operator, cmds[i].last);
		j = 0;
		while (j < cmds[i].len)
		{
			printf("pipes[%zu].in=%s\n", j, cmds[i].pipes[j].in_file);
			printf("pipes[%zu].out=%s\n", j, cmds[i].pipes[j].out_file);
			printf("pipes[%zu].cmd=%s\n", j, cmds[i].pipes[j].cmd);
			k = 0;
			while (cmds[i].pipes[j].have_param && cmds[i].pipes[j].param[k])
			{
				printf("pipes[%zu].param=%s\n", j, cmds[i].pipes[j].param[k]);
				k++;
				//i++;
			}
			j++;
		}
		if (cmds[i].last)
			break ;
		i++;
	}
}

t_cmds	*parser(t_token *tokens)
{
	t_cmds	*cmds;
	int	error;
	//size_t	cmds_num;

	parser_expand(tokens, NON, 0);
	put_tokens(tokens);
	cmds = init_parser(tokens, &error);
	if (error)
		kill_myprocess(12, NULL, tokens, NULL);
	if (!cmds)
		return (NULL);
	create_heredoc_file(tokens);
	if (search_std_in_and_out(tokens, cmds))
	{
		search_cmds_and_arg(tokens, cmds);
	}
	printf("print cmds test No.2\n");
	print_comds(cmds);

	//cmds_num = count_comds(tokens);
	//////////cmds = (t_cmd *)malloc(sizeof(t_cmd) * (cmds_num + 1));
	//parser_expand(tokens);
	//create_heredoc_file(tokens);
	//search_std_in_and_out(tokens, cmds);
	//cmds[cmds_num].last = true;
	//cmds[0].in = (int)(tokens[0].type);
	return (cmds);
}
