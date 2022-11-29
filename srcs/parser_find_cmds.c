/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:55:40 by hsano             #+#    #+#             */
/*   Updated: 2022/11/29 18:49:06 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_find_cmds.h"
#include "parser_find_cmds_util.h"
#include "cmd_builtin.h"
#include "token_parenthesis.h"
#include "parser_error.h"
#include "libft_mem.h"
#include "libft_sort.h"

static int	set_cmd_name(t_cmds *cmds, t_token *token, size_t pipe_i)
{
	cmds->pipes[pipe_i].cmd = token->literal;
	cmds->pipes[pipe_i].is_builtin_cmd = is_builtin(&token->literal);
	return (true);
}

static char	**insert_argv(t_token *tokens, char **argv, size_t i, size_t *j)
{
	char	**split;
	size_t	k;

	if (tokens[i].type == IDENT && tokens[i].valid && tokens[i].expand)
	{
		split = ft_split(tokens[i].literal, PARSER_DELIMITER);
		if (!split && set_parser_error(true))
			return (argv);
		k = 0;
		ft_qsort(split, 0);
		while (split && split[k])
			argv[(*j)++] = split[k++];
		free(split);
	}
	else if (tokens[i].type == IDENT && tokens[i].valid)
	{
		argv[(*j)++] = ft_strdup(tokens[i].literal);
		if (argv[*j - 1] == NULL)
			set_parser_error(true);
	}
	return (argv);
}

static char	**allocate_args_memory(t_token *tokens, size_t i \
		, size_t len)
{
	char	**argv;
	size_t	j;

	j = 0;
	if (get_parser_error())
		return (NULL);
	argv = ft_calloc(sizeof(char *), len + 1);
	if (!argv && set_parser_error(true))
		return (NULL);
	while (tokens[i].type != EOS)
	{
		if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND \
				|| tokens[i].type == PIPE)
			break ;
		argv = insert_argv(tokens, argv, i, &j);
		if (get_parser_error())
		{
			ft_free_split(argv);
			return (NULL);
		}
		i++;
	}
	return (argv);
}

static void	set_args(t_cmds *cmds, t_token *tokens \
		, size_t *tmp_i, size_t pipe_i)
{
	size_t	backup_i;
	size_t	cnt;
	size_t	i;

	i = *tmp_i;
	backup_i = *tmp_i;
	cnt = 0;
	cmds->pipes[pipe_i].have_param = true;
	while (tokens[i].type != EOS)
	{
		if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND \
				|| tokens[i].type == PIPE)
			break ;
		else if (tokens[i].type == IDENT && tokens[i].valid)
			cnt += cnt_parser_cmd_param(&tokens[i]);
		i++;
	}
	cmds->pipes[pipe_i].param = allocate_args_memory(tokens, backup_i, cnt);
	cmds->pipes[pipe_i].param_num = cnt;
	*tmp_i = --i;
}

int	search_cmds_and_arg(t_token *tokens, t_cmds *cmds, size_t i)
{
	size_t	ci;
	size_t	pi;

	i = 0;
	ci = 0;
	pi = 0;
	while (tokens[i].type != EOS)
	{
		if (!tokens[i].valid && ++i)
			continue ;
		else if (tokens[i].type == LPAREN || tokens[i].type == RPAREN)
			i = set_paren(tokens, &(cmds[ci]), i, pi);
		else if ((tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND) \
				&& ++ci)
			pi = 0;
		else if (tokens[i].type == PIPE)
			pi++;
		else if (tokens[i].type == IDENT && cmds[ci].pipes[pi].cmd == NULL \
				&& set_cmd_name(&(cmds[ci]), &(tokens[i]), pi))
			continue ;
		else if (tokens[i].type == IDENT && cmds[ci].pipes[pi].cmd != NULL)
			set_args(&(cmds[ci]), tokens, &i, pi);
		i++;
	}
	return (!get_parser_error());
}
