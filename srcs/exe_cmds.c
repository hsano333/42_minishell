/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/14 04:03:05 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmds.h"
#include "env.h"
#include "cmd_builtin.h"
#include "signal_minishell.h"
#include "parser_util.h"

int	is_continue(t_cmds *cmds, int rval, size_t i)
{
	if (i > 0)
	{
		if (i > 0 && (cmds[i - 1].operator == D_PIPE && rval == 0) && ++i)
			return (true);
		else if (i > 0 && (cmds[i - 1].operator == D_AMPERSAND \
					&& rval > 0 && rval < 256 && ++i))
			return (true);
	}
	return (false);
}

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

void	exe_cmds(t_token *tokens)
{
	size_t	i;
	size_t	j;
	char	**envv;
	int		rval;
	t_cmds	*cmds;
	t_token_type	type;

	i = 0;
	rval = 0;
	j = 0;
	type = NON;
	while (tokens[i].type != EOS)
	{
		while (tokens[i].type != EOS && tokens[i].type != D_AMPERSAND \
				&& tokens[i].type != D_PIPE)
			i++;
		type = tokens[i].type;
		if (type != EOS)
			tokens[i].type = EOS;
		i++;
		cmds = parser(&(tokens[j]));
		if (j > 0 && ((type == D_PIPE && rval != 0) || (type == D_AMPERSAND && rval == 0)))
		{
			j = i;
			clear_all_cmds(&cmds);
			continue ;
		}
		j = i;
		envv = env_store(NULL, GET_ENV);
		handle_cmd_signals();
		if (cmds[0].len > 1 || (cmds[0].len == 1 \
					&& !cmds[0].pipes[0].is_builtin_cmd))
			rval = pipex(&(cmds[0]), envv);
		else if (change_buildin_fd(&(cmds[0].pipes[0]), false))
		{
			rval = exec_builtin_cmd(cmds[0].pipes[0].param);
			change_buildin_fd(&(cmds[0].pipes[0]), true);
		}
		handle_global_signals();
		set_exit_status(rval);
		clear_all_cmds(&cmds);
		if (type == EOS)
			break ;
	}
}
