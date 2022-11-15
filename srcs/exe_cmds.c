/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/16 01:19:45 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmds.h"
#include "cmd_builtin.h"
#include "signal_minishell.h"
#include "parser_util.h"
#include "libft_put.h"
#include "lexer.h"
#include "lexer_util.h"
#define RESET_INDEX (INT_MIN)

static int	change_buildin_fd_inout(int fd_inout \
		, char *filename, int option, int *fd)
{
	*fd = fd_inout;
	if (filename)
	{
		close(*fd);
		*fd = open(filename, option);
		if (*fd < 0)
		{
			ft_putstr_fd("open error:", 2);
			write(2, filename, ft_strlen(filename));
			write(2, "\n", 1);
			return (false);
		}
	}
	if (dup2(*fd, fd_inout) == -1)
		return (false);
	return (true);
}

static int	change_buildin_fd(t_pipe *pipe, int back)
{
	static int	pre_fd_in = 0;
	static int	pre_fd_out = 1;
	static int	fd_in = 0;
	static int	fd_out = 1;

	if (back == false)
	{
		pre_fd_in = dup(pipe->option_fd_in);
		pre_fd_out = dup(pipe->option_fd_out);
		change_buildin_fd_inout(pipe->option_fd_in \
		, pipe->in_file, O_RDONLY, &fd_in);
		change_buildin_fd_inout(pipe->option_fd_out \
		, pipe->out_file, O_APPEND | O_WRONLY, &fd_out);
	}
	if (back == true)
	{
		if (fd_out != 1)
			close(fd_out);
		if (fd_in != 1)
			close(fd_in);
		dup2(pre_fd_in, 0);
		dup2(pre_fd_out, 1);
	}
	return (true);
}

t_cmds	*get_cmds(t_token *tokens, int rval, t_token_type *type, size_t i)
{
	static size_t	j = 0;
	t_cmds			*cmds;

	i = j;
	//printf("get_cmds  start\n");
	//put_tokens(tokens);
	//printf("get_cmds  start i=%zu\n", i);
	if (rval == RESET_INDEX)
		j = 0;
	if (rval == RESET_INDEX)
		return (NULL);
	while (tokens[i].type != EOS && tokens[i].type != D_AMPERSAND \
			&& tokens[i].type != D_PIPE)
	{
		if (tokens[i].type == LPAREN)
			while (tokens[++i].type != EOS && tokens[i].type != LPAREN)
				;
				//i++;
		if (tokens[i].type != EOS)
			i++;
	}
	//printf("get_cmds  No.2  start i=%zu\n", i);


	if (j > 0 && ((*type == D_PIPE && rval == 0) \
				|| (*type == D_AMPERSAND && rval != 0)))
	{
		*type = tokens[i].type;
		j = i + 1;
		return (NULL);
	}
	*type = tokens[i].type;
	if (*type != EOS)
		tokens[i].type = EOS;
	cmds = parser(&(tokens[j]));
	tokens[i].type = *type;
	j = i + 1;
	return (cmds);
}

void	exe_cmds(t_token *tokens, int subshell)
{
	int				rval;
	t_cmds			*cmds;
	t_token_type	type;

	rval = 0;
	type = NON;
	if (subshell)
		printf("start exe_cmds\n");
	//put_tokens(tokens);
	//write(2, "start exe cmds error out\n", 25);
	//write(1, "start exe cmds std out\n", 23);
	cmds = get_cmds(tokens, RESET_INDEX, &type, 0);
	while (tokens[0].type != EOS && type != EOS)
	{
		cmds = get_cmds(tokens, rval, &type, 0);
		if (!cmds)
			continue ;
		handle_cmd_signals();
		if (cmds[0].len > 1 || cmds->has_subshell || (cmds[0].len == 1 \
					&& !cmds[0].pipes[0].is_builtin_cmd))
			rval = pipex(&(cmds[0]));
		else if (change_buildin_fd(&(cmds[0].pipes[0]), false))
		{
			rval = exec_builtin_cmd(cmds[0].pipes[0].param);
			change_buildin_fd(&(cmds[0].pipes[0]), true);
		}
		handle_global_signals();
		set_exit_status(rval);
		clear_all_cmds(&cmds);
	}
}
