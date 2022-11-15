/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:06:43 by hsano             #+#    #+#             */
/*   Updated: 2022/11/16 03:16:18 by hsano            ###   ########.fr       */
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
#include "token_parenthesis.h"

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
			printf("%zu.pipes[%zu].sub_tokens=%p\n", i, j, cmds[i].pipes[j].sub_tokens);
			if (cmds[i].pipes[j].sub_tokens)
			{
				printf("put_tokens subshell\n");
				put_tokens(cmds[i].pipes[j].sub_tokens);
			}
			printf("%zu.pipes[%zu].sub_tokens=%zu\n", i, j, cmds[i].pipes[j].sub_tokens_size);
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

static size_t	concat_str(t_token *tokens, size_t i, size_t j, int *f)
{
	char	*tmp;

	*f = false;
	if (j == 0)
		return (0);
	tmp = ft_strjoin(tokens[i].literal, tokens[j].literal);
	free(tokens[i].literal);
	tokens[i].literal = tmp;
	return (i);
}

static size_t	concat(t_token *tokens, size_t i, int b_flag, int *f_flag)
{
	size_t	j;

	while (!((tokens[i].type == IDENT && tokens[i].valid) \
					|| tokens[i].type == EOS))
		i++;
	if (tokens[i].type == EOS)
		return (0);
	if (b_flag)
	{
		tokens[i].valid = false;
		return (i);
	}
	else if (b_flag == false && tokens[i].concat_back)
		concat_str(tokens, i, concat(tokens, i + 1, true, f_flag), f_flag);
	else if (b_flag == false && tokens[i].concat_front)
	{
		*f_flag = true;
		tokens[i].valid = false;
		return (i);
	}
	j = concat(tokens, i + 1, false, f_flag);
	if (*f_flag)
		concat_str(tokens, i, j, f_flag);
	return (i);
}

t_cmds	*parser(t_token *tokens)
{
	t_cmds	*cmds;
	int		error;
	int		tmp_flag;

	parser_expand(tokens, NON, 0);
	concat(tokens, 0, false, &tmp_flag);
	cmds = init_parser(tokens, &error);
	if (error)
		kill_myprocess(12, NULL, tokens, NULL);
	if (!cmds)
		return (NULL);
	if (create_heredoc_file(tokens) == false)
		return (NULL);
	if (search_std_in_and_out(tokens, cmds, 0))
	{
		//put_tokens(tokens);
		if (search_cmds_and_arg(tokens, cmds, 0))
			clear_all_cmds(&cmds);
		if (!cmds)
			ft_putstr_fd("minishell:invalid command\n", 2);
	}
	enable_paren_token(cmds);
	return (cmds);
}
