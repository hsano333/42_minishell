/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:06:43 by hsano             #+#    #+#             */
/*   Updated: 2022/11/19 00:16:25 by hsano            ###   ########.fr       */
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

static size_t	concat_str(t_token *tokens, size_t i, size_t j, int *f)
{
	char	*tmp;

	*f = false;
	if (j == 0 || get_parser_error())
		return (0);
	tmp = ft_strjoin(tokens[i].literal, tokens[j].literal);
	if (!tmp)
		set_parser_error(true);
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
	if (tokens[i].type == EOS || get_parser_error())
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

	set_parser_error(false);
	put_tokens(tokens);
	parser_expand(tokens, NON, 0);
	put_tokens(tokens);
	concat(tokens, 0, false, &tmp_flag);
	cmds = init_parser(tokens, &error);
	if (get_parser_error() && parser_error(12, cmds))
		return (NULL);
	if (!search_std_in_and_out(tokens, cmds, 0) && parser_error(0, cmds))
		return (NULL);
	if (!search_cmds_and_arg(tokens, cmds, 0) && parser_error(12, cmds))
		return (NULL);
	print_cmds(cmds);
	return (cmds);
}
