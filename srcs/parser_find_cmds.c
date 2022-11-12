/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:55:40 by hsano             #+#    #+#             */
/*   Updated: 2022/11/12 16:12:01 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_find_cmds.h"
#include "parser_find_cmds_util.h"
#include "cmd_builtin.h"

static void	set_cmd_name(t_cmds *cmds, t_token *token, size_t pipe_i)
{
	cmds->pipes[pipe_i].cmd = token->literal;
	cmds->pipes[pipe_i].is_builtin_cmd = is_builtin(&token->literal);
}

static char	**allocate_args_memory(t_token *tokens, size_t i \
		, size_t len, size_t j)
{
	char	**argv;
	char	**split;
	size_t	k;

	argv = (char **)malloc(sizeof(char *) * (len + 1));
	while (argv && tokens[i].type != EOS)
	{
		argv[len] = NULL;
		if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND \
				|| tokens[i].type == PIPE)
			break ;
		else if (tokens[i].type == IDENT && tokens[i].valid && tokens[i].expand)
		{
			split = ft_split(tokens[i].literal, PARSER_DELIMITER);
			k = 0;
			while (split && split[k])
				argv[j++] = split[k++];
			free(split);
		}
		else if (tokens[i].type == IDENT && tokens[i].valid)
			argv[j++] = tokens[i].literal;
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
	cmds->pipes[pipe_i].param = allocate_args_memory(tokens, backup_i, cnt, 0);
	*tmp_i = --i;
}

static int	have_error(t_cmds *cmds)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmds)
	{
		j = 0;
		while (j < cmds[i].len)
		{
			if (cmds[i].pipes[j].have_param && cmds[i].pipes[j].param == NULL)
				return (false);
			j++;
		}
		if (cmds[i].last == true)
			break ;
		i++;
	}
	return (false);
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
		else if ((tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND) \
				&& ++ci)
			pi = 0;
		else if (tokens[i].type == PIPE)
			pi++;
		else if (tokens[i].type == IDENT && cmds[ci].pipes[pi].cmd == NULL)
		{
			set_cmd_name(&(cmds[ci]), &(tokens[i]), pi);
			continue ;
		}
		else if (tokens[i].type == IDENT && cmds[ci].pipes[pi].cmd != NULL)
			set_args(&(cmds[ci]), tokens, &i, pi);
		i++;
	}
	return (!have_error(cmds));
}
