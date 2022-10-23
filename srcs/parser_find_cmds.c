/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:55:40 by hsano             #+#    #+#             */
/*   Updated: 2022/10/23 16:44:30 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_find_cmds.h"

static void	set_cmd_name(t_cmds *cmds, t_token *token, size_t pipe_i)
{
	cmds->pipes[pipe_i].cmd = token->literal;
	if (ft_strncmp(token->literal, "echo", ft_strlen("echo") + 1) == 0)
		cmds->pipes[pipe_i].builtin = BUIDIN_ECHO;
	else if (ft_strncmp(token->literal, "cd", ft_strlen("cd") + 1) == 0)
		cmds->pipes[pipe_i].builtin = BUIDIN_CD;
	else if (ft_strncmp(token->literal, "pwd", ft_strlen("pwd") + 1) == 0)
		cmds->pipes[pipe_i].builtin = BUIDIN_PWD;
	else if (ft_strncmp(token->literal, "export", ft_strlen("export") + 1) == 0)
		cmds->pipes[pipe_i].builtin = BUIDIN_EXPORT;
	else if (ft_strncmp(token->literal, "unset", ft_strlen("unset") + 1) == 0)
		cmds->pipes[pipe_i].builtin = BUIDIN_UNSET;
	else if (ft_strncmp(token->literal, "env", ft_strlen("env") + 1) == 0)
		cmds->pipes[pipe_i].builtin = BUIDIN_ENV;
	else if (ft_strncmp(token->literal, "exit", ft_strlen("exit") + 1) == 0)
		cmds->pipes[pipe_i].builtin = BUIDIN_EXIT;
	else
		cmds->pipes[pipe_i].builtin = NOT_BUIDIN;
}

static char	**allocate_args_memory(t_token *tokens, size_t i, size_t len)
{
	char	**argv;
	size_t	j;

	argv = (char **)malloc(sizeof(char *) * (len + 1));
	if (!argv)
		return (NULL);
	argv[len] = NULL;
	j = 0;
	while (tokens[i].type != EOS)
	{
		if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND || tokens[i].type == PIPE)
			break ;
		else if (tokens[i].type == IDENT && tokens[i].valid)
		{
			argv[j++] = tokens[i].literal;
		}
		i++;
	}
	return (argv);
}

static void	set_args(t_cmds *cmds, t_token *tokens, size_t i, size_t pipe_i)
{
	//size_t	len;
	size_t	backup_i;
	size_t	cnt;

	backup_i = i;
	//len = 0;
	cnt = 0;
	cmds->pipes[pipe_i].have_param = true;
	while (tokens[i].type != EOS)
	{
		if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND || tokens[i].type == PIPE)
			break ;
		else if (tokens[i].type == IDENT && tokens[i].valid)
		{
			cnt++;
			//len += ft_strlen(tokens[i].literal) + 1;
			//cmds->
		}
		i++;
	}
	cmds->pipes[pipe_i].param = allocate_args_memory(tokens, backup_i, cnt);
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
			if (cmds[i].pipes[j].have_param &&  cmds[i].pipes[j].param == NULL)
				return (false);
			j++;

		}
		if (cmds[i].last == true)
			break ;
		i++;
	}
	return (false);
}


int	search_cmds_and_arg(t_token *tokens, t_cmds *cmds)
{
	size_t	i;
	size_t	cmd_i;
	size_t	pipe_i;

	i = 0;
	cmd_i = 0;
	pipe_i = 0;
	while (tokens[i].type != EOS)
	{
		if (!tokens[i].valid && ++i)
			continue ;
		else if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND)
		{
			cmd_i++;
			pipe_i = 0;
		}
		else if (tokens[i].type == PIPE)
			pipe_i++;
		else if (tokens[i].type == IDENT && cmds[cmd_i].pipes[pipe_i].cmd == NULL)
			set_cmd_name(&(cmds[cmd_i]), &(tokens[i]), pipe_i);
		else if (tokens[i].type == IDENT && cmds[cmd_i].pipes[pipe_i].cmd != NULL)
			set_args(&(cmds[cmd_i]), tokens, i, pipe_i);
		i++;
	}
	if (have_error(cmds))
		return (false);
	return (true);
}
