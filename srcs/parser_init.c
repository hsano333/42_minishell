/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:43:36 by hsano             #+#    #+#             */
/*   Updated: 2022/11/04 18:21:24 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_init.h"
#include "parser_util.h"
#include "lexer_util.h"
#include <stdio.h>

static size_t	count_comds(t_token *tokens)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	if (tokens[i].type == EOS)
		return (0);
	cnt = 1;
	while (tokens[i].type != EOS)
	{
		if (!tokens[i].valid && ++i)
			continue ;
		if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND)
			cnt++;
		i++;
	}
	return (cnt);
}

static t_pipe	*init_pipe(size_t len)
{
	t_pipe	*pipes;
	size_t	i;

	i = 0;
	pipes = (t_pipe *)malloc(sizeof(t_pipe) * len);
	if (!pipes)
		return (NULL);
	while (i < len)
	{
		pipes[i].in_file = NULL;
		pipes[i].out_file = NULL;
		pipes[i].cmd = NULL;
		pipes[i].have_param = false;
		pipes[i].param = NULL;
		pipes[i].id = 0;
		pipes[i].is_builtin_cmd = false;
		i++;
	}
	return (pipes);
}

static int	init_cmds(t_cmds *cmds, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		cmds[i].result = false;
		cmds[i].id = i;
		cmds[i].pipes = NULL;
		cmds[i].len = 0;
		cmds[i].operator = NON;
		cmds[i].last = false;
		i++;
	}
	return (true);
}

static t_cmds	*init_pipes(t_token *tokens, t_cmds *cmds \
		, size_t cnt_cmds, size_t cnt_pipes)
{
	size_t	i;

	i = 0;
	while (tokens[i].type != EOS)
	{
		if (tokens[i].type == PIPE)
			cnt_pipes++;
		if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND)
		{
			cmds[cnt_cmds].pipes = init_pipe(cnt_pipes);
			if (!cmds[cnt_cmds].pipes)
				return (cmds);
			cmds[cnt_cmds].len = cnt_pipes;
			cmds[cnt_cmds].operator = tokens[i].type;
			cnt_pipes = 1;
			cnt_cmds++;
		}
		i++;
	}
	cmds[cnt_cmds].pipes = init_pipe(cnt_pipes);
	cmds[cnt_cmds].len = cnt_pipes;
	return (cmds);
}

t_cmds	*init_parser(t_token *tokens, int *error)
{
	t_cmds	*cmds;
	size_t	cmds_num;

	cmds_num = count_comds(tokens);
	if (cmds_num == 0)
		return (NULL);
	*error = true;
	cmds = (t_cmds *)malloc(sizeof(t_cmds) * (cmds_num));
	if (!cmds)
		return (NULL);
	init_cmds(cmds, cmds_num);
	cmds[cmds_num - 1].last = true;
	cmds = init_pipes(tokens, cmds, 0, 1);
	if (is_error_cmds(cmds))
		clear_all_cmds(&cmds);
	*error = false;
	return (cmds);
}
