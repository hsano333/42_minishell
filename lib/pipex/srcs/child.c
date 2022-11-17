/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:58:19 by hsano             #+#    #+#             */
/*   Updated: 2022/11/18 02:29:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"
#include "cmd_builtin.h"
#include "exe_cmds.h"
#include "lexer_util.h"
#include "token_parenthesis.h"

static void	put_invalid_command(char *cmds)
{
	write(2, "minishell: command not found:", 29);
	write(2, cmds, ft_strlen(cmds));
	write(2, "\n", 1);
	exit(127);
}

static	void	change_fd(int fd_in, int *pipe_fd, t_pipe *pipes)
{
	int			r[2];

	close(pipe_fd[PIPE_IN]);
	if (pipes->in_file)
	{
		close(fd_in);
		fd_in = open(pipes->in_file, O_RDONLY);
		if (fd_in < 0)
			kill_process(-1, pipes->in_file, NULL);
	}
	r[0] = dup2(fd_in, pipes->option_fd_in);
	r[1] = 1;
	if (pipe_fd[PIPE_OUT] != 1)
		r[1] = dup2(pipe_fd[PIPE_OUT], pipes->option_fd_out);
	if (r[0] == -1 || r[1] == -1)
		exit(EXIT_FAILURE);
}

void	child(int fd_in, int *pipe_fd, t_pipe *pipes, char **environ)
{
	char		filepath[PATH_MAX + 1];

	if (pipes->param || pipes->sub_tokens)
	{
		change_fd(fd_in, pipe_fd, pipes);
		if (pipes->sub_tokens && enable_paren_token(pipes))
		{
			pipes->sub_tokens[pipes->sub_tokens_size].type = EOS;
			pipes->option_fd_in = fd_in;
			exe_cmds(pipes->sub_tokens);
			exit(get_exit_status());
		}
		else if (is_builtin(pipes->param))
			exec_builtin_cmd(pipes->param);
		else
		{
			if (search_path(pipes->param[0], filepath))
			{
				if (execve(filepath, pipes->param, environ) == -1)
					put_invalid_command(filepath);
			}
			else
				put_invalid_command(pipes->param[0]);
		}
	}
}
