/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:55:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/18 01:11:59 by hsano            ###   ########.fr       */
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
	size_t		bk = 0;
	t_cmds		*cmds;
	t_token_type	old_type;

	bk = *i;
	old_type = *type;
	//printf("get_cmds start No.1 tokens[*i].type=%d, i=%zu\n", tokens[*i].type, *i);
	while (tokens[*i].type != EOS && ((tokens[*i].type != D_AMPERSAND && tokens[*i].type != D_PIPE) \
			|| (!tokens[*i].valid && (tokens[*i].type == D_AMPERSAND || tokens[*i].type == D_PIPE))))
		(*i)++;
	//printf("get_cmds start No.2 tokens[*i].type=%d, i=%zu\n", tokens[*i].type, *i);
	*type = tokens[*i].type;
	if (bk > 0 && ((old_type == D_PIPE && rval == 0) \
				|| (old_type == D_AMPERSAND && rval != 0)))
	{
	//printf("get_cmds start No.3 tokens[*i].type=%d, i=%zu, type=%d\n", tokens[*i].type, *i, *type);
		if (*type != EOS)
			(*i)++;
		return (NULL);
	}
	//printf("get_cmds start No.4 tokens[*i].type=%d, i=%zu, *type=%d\n", tokens[*i].type, *i, *type);
	if (*type != EOS)
	{
	//printf("get_cmds start No.5 tokens[*i].type=%d, i=%zu\n", tokens[*i].type, *i);
		tokens[*i].type = EOS;
	}
	//printf("get_cmds start No.6 tokens[*i].type=%d, i=%zu, *type=%d,, bk=%zu, tokens[bk].type=%s\n", tokens[*i].type, *i, *type, bk, tokens[bk].literal);
	//put_tokens(&(tokens[bk]));
	change_token_no(&(tokens[bk]));
	cmds = parser(&(tokens[bk]));
	tokens[*i].type = *type;
	//printf("get_cmds start No.7 tokens[*i].type=%d, i=%zu, type=%d\n", tokens[*i].type, *i, *type);
	if (*type != EOS)
	{
	//printf("get_cmds start No.8 tokens[*i].type=%d, i=%zu\n", tokens[*i].type, *i);
		(*i)++;
	}
	//printf("get_cmds start No.9 tokens[*i].type=%d, i=%zu\n", tokens[*i].type, *i);
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
		printf("exe_cmds No.1 i=%zu\n", i);
		cmds = get_cmds(tokens, rval, &i, &type);
		printf("exe_cmds No.2 i=%zu\n", i);
		if (!cmds)
			continue ;
		printf("exe_cmds No.3 i=%zu\n", i);
		handle_cmd_signals();
		if ((cmds[0].len == 1 && cmds[0].pipes[0].is_builtin_cmd && change_buildin_fd(&(cmds[0].pipes[0]), false)))
		{
		printf("exe_cmds No.4 i=%zu\n", i);
			rval = exec_builtin_cmd(cmds[0].pipes[0].param);
			change_buildin_fd(&(cmds[0].pipes[0]), true);
		}
		else if (cmds->has_subshell || cmds[0].len >= 1)
		{
		printf("exe_cmds No.5 i=%zu\n", i);
			rval = pipex(&(cmds[0]));
		}
		printf("exe_cmds No.6 i=%zu\n", i);
		handle_global_signals();
		set_exit_status(rval);
		printf("clear all_cmds No.0\n");
		clear_all_cmds(&cmds);
		printf("exe_cmds No.7 i=%zu\n", i);
		//i++;
	}
	//printf("exe_cmds No.4 i=%zu\n", i);
	return (get_exit_status());
}
