/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:06:43 by hsano             #+#    #+#             */
/*   Updated: 2022/11/10 17:27:43 by hsano            ###   ########.fr       */
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
		j = 0;
		while (j < cmds[i].len)
		{
			printf("%zu.pipes[%zu].in=%s\n", i, j, cmds[i].pipes[j].in_file);
			printf("%zu.pipes[%zu].out=%s\n", i, j, cmds[i].pipes[j].out_file);
			printf("%zu.pipes[%zu].cmd=%s\n", i, j, cmds[i].pipes[j].cmd);
			k = 0;
			while (cmds[i].pipes[j].have_param && cmds[i].pipes[j].param[k])
			{
				printf("pipes[%zu].param[%zu]=%s\n", j, k \
						, cmds[i].pipes[j].param[k]);
				k++;
			}
			j++;
		}
		if (cmds[i++].last)
			break ;
	}
}

static void	disable_space(t_token *tokens)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tokens[i].type != EOS)
	{
		if (tokens[i].type == WHITE_SPACE)
		{
			if (j == 0)
				j = i + 1;
			while (tokens[j].type != EOS)
			{
				if (tokens[i].type != WHITE_SPACE)
					j++;
			}
		}
		i++;
	}
}

void	parser_concat(t_token *tokens)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tokens[i].type != EOS)
	{
		if (tokens[i].type == WHITE_SPACE)
		{
			if (j == 0)
				j = i + 1;
			while (tokens[j].type != EOS)
			{
				if (tokens[i].type != WHITE_SPACE)
					j++;
			}
		}
		i++;
	}
}

t_cmds	*parser(t_token *tokens)
{
	t_cmds	*cmds;
	int		error;

	parser_expand(tokens, NON, 0);
	disable_space(tokens);
	cmds = init_parser(tokens, &error);
	if (error)
		kill_myprocess(12, NULL, tokens, NULL);
	if (!cmds)
		return (NULL);
	if (create_heredoc_file(tokens) == false)
		return (NULL);
	if (search_std_in_and_out(tokens, cmds, 0))
		search_cmds_and_arg(tokens, cmds, 0);
	return (cmds);
}
