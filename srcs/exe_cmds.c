/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/20 10:55:36 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmds.h"
#include "cmd_builtin.h"
#include "signal_minishell.h"
#include "parser_util.h"
#include "libft_put.h"
#include "lexer.h"
#include "lexer_util.h"
#include "lexer_quote_flag.h"
#include "token_type.h"
#define RESET_INDEX (INT_MIN)

int	change_token_no(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i].type != EOS)
	{
		tokens[i].id = i;
		i++;
	}
	return (true);
}

t_cmds	*get_cmds(t_token *tokens, int rval, size_t *i, t_token_type *type)
{
	size_t			bk;
	t_cmds			*cmds;
	t_token_type	old_type;

	bk = *i;
	old_type = *type;
	set_lexer_quote(NON);
	while (tokens[*i].type != EOS)
	{
		set_lexer_quote_util(tokens[*i].type);
		if (get_lexer_quote() == NON && tokens[*i].valid \
				&& !not_if_token(tokens[*i].type))
			break ;
		(*i)++;
	}
	*type = tokens[*i].type;
	if (bk > 0 && ((old_type == D_PIPE && rval == 0) \
				|| (old_type == D_AMPERSAND && rval != 0)))
		return (NULL);
	if (*type != EOS)
		tokens[*i].type = EOS;
	change_token_no(&(tokens[bk]));
	cmds = parser(&(tokens[bk]));
	tokens[*i].type = *type;
	return (cmds);
}

int	exe_cmds(t_token *tokens)
{
	int				rval;
	t_cmds			*cmds;
	t_token_type	type;
	size_t			i;

	i = 0;
	rval = 0;
	while (tokens[i].type != EOS)
	{
		cmds = get_cmds(tokens, rval, &i, &type);
		handle_ign_signals();
		if (cmds && (cmds[0].len == 1 && cmds[0].pipes[0].is_builtin_cmd))
			rval = builtin_wrapper(cmds[0].pipes[0].param, &(cmds[0].pipes[0]));
		else if (cmds && (cmds->has_subshell || cmds[0].len >= 1))
			rval = pipex(&(cmds[0]));
		else
			rval = 1;
		set_exit_status(rval);
		handle_global_signals();
		clear_all_cmds(&cmds);
		if (type != EOS)
			i++;
	}
	return (rval);
}
