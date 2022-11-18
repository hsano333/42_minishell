/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:06:43 by hsano             #+#    #+#             */
/*   Updated: 2022/11/19 04:11:56 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_init.h"
#include "parser_expand.h"
#include "parser_std.h"
#include "stdio.h"
#include "parser_find_cmds.h"
#include "kill_myprocess.h"
#include "token_parenthesis.h"
#include "parser_error.h"
#include "parser_util.h"
#include "parser_concat.h"

void	print_cmds(t_cmds *cmds)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (cmds)
	{
		j = 0;
		while (j < cmds[i].len)
		{
			printf("%zu.pipes[%zu].in=%s\n", i, j, cmds[i].pipes[j].in_file);
			printf("%zu.pipes[%zu].out=%s\n", i, j, cmds[i].pipes[j].out_file);
			printf("%zu.pipes[%zu].cmd=%s\n", i, j, cmds[i].pipes[j].cmd);
			if (cmds[i].pipes[j].sub_tokens)
				put_tokens(cmds[i].pipes[j].sub_tokens);
			k = -1;
			while (cmds[i].pipes[j].have_param && cmds[i].pipes[j].param[++k])
				printf("%zu.pipes[%zu].param[%zu]=%s\n" \
						, i, j, k, cmds[i].pipes[j].param[k]);
			j++;
		}
		if (cmds[i++].last)
			break ;
	}
}

t_cmds	*parser(t_token *tokens)
{
	t_cmds	*cmds;
	int		error;

	set_parser_error(false);
	parser_expand(tokens, NON, 0);
	parser_concat(tokens);
	if (get_parser_error())
		return (NULL);
	cmds = init_parser(tokens, &error);
	if (get_parser_error() && parser_error(12, cmds))
		return (NULL);
	if (!search_std_in_and_out(tokens, cmds, 0) && parser_error(0, cmds))
		return (NULL);
	if (!search_cmds_and_arg(tokens, cmds, 0) && parser_error(12, cmds))
		return (NULL);
	return (cmds);
}
