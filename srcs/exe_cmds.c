/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/16 16:52:43 by hsano            ###   ########.fr       */
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

t_cmds	*get_cmds(t_token *tokens, int rval, size_t *i, t_token_type *type)
{
	size_t		bk = 0;
	t_cmds		*cmds;
	t_token_type	old_type;

	bk = *i;
	old_type = *type;
	while (tokens[*i].type != EOS && ((tokens[*i].type != D_AMPERSAND && tokens[*i].type != D_PIPE) \
			|| (!tokens[*i].valid && (tokens[*i].type == D_AMPERSAND || tokens[*i].type == D_PIPE))))
		(*i)++;
	*type = tokens[*i].type;
	if (bk > 0 && ((old_type == D_PIPE && rval == 0) \
				|| (old_type == D_AMPERSAND && rval != 0)))
	{
		if (*type != EOS)
			(*i)++;
		return (NULL);
	}
	if (*type != EOS)
		tokens[*i].type = EOS;
	cmds = parser(&(tokens[bk]));
	tokens[*i].type = *type;
	if (*type != EOS)
		(*i)++;
	return (cmds);
}

int	exe_cmds(t_token *tokens)
{
	int				rval;
	t_cmds			*cmds;
	t_token_type	type;
	size_t	i;

	i = 0;
	rval = 0;
	//type = NON;
	//if (subshell)
		//printf("start exe_cmds\n");
	//put_tokens(tokens);
	//write(2, "start exe cmds error out\n", 25);
	//write(1, "start exe cmds std out\n", 23);
	//cmds = get_cmds(tokens, RESET_INDEX, &i);
	while (tokens[i].type != EOS)
	{
		cmds = get_cmds(tokens, rval, &i, &type);
		if (!cmds)
			continue ;
		handle_cmd_signals();
		if ((cmds[0].len == 1 && cmds[0].pipes[0].is_builtin_cmd && change_buildin_fd(&(cmds[0].pipes[0]), false)))
		{
			rval = exec_builtin_cmd(cmds[0].pipes[0].param);
			change_buildin_fd(&(cmds[0].pipes[0]), true);
		}
		else if (cmds->has_subshell || cmds[0].len >= 1)
			rval = pipex(&(cmds[0]));
		handle_global_signals();
		set_exit_status(rval);
		clear_all_cmds(&cmds);
	}
	return (get_exit_status());
}
