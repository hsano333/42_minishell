/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_change_std.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:52:31 by hsano             #+#    #+#             */
/*   Updated: 2022/11/19 14:07:37 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parser_std.h"
#include "parser_heredoc.h"
#include "token_type.h"

static int	create_file(char *filename, int option)
{
	int		fd_out;

	fd_out = open(filename, option, 0744);
	if (fd_out < 0 && option == (O_APPEND | O_WRONLY))
	{
		option = O_CREAT | O_WRONLY ;
		fd_out = open(filename, option, 0744);
		if (fd_out < 0)
		{
			perror(filename);
			return (false);
		}
	}
	else if (fd_out < 0)
		return (false);
	close(fd_out);
	return (true);
}

int	change_std_glt(t_cmds *cmds, t_token *tokens, size_t i, size_t pipe_i)
{
	int	rval;

	rval = true;
	if (tokens[i + 1].type == IDENT)
	{
		tokens[i + 1].valid = false;
		if (access(tokens[i + 1].literal, F_OK) != 0)
			rval = create_file(tokens[i + 1].literal, O_WRONLY | O_CREAT);
		if (!rval)
			return (rval);
		cmds->pipes[pipe_i].out_file = NULL;
		cmds->pipes[pipe_i].in_file = tokens[i + 1].literal;
		cmds->pipes[pipe_i].option_fd_in = tokens[i].option_fd;
	}
	return (true);
}

int	change_std_in(t_cmds *cmds, t_token *tokens, size_t i, size_t pipe_i)
{
	int	rval;
	int	pre_type;

	rval = true;
	pre_type = tokens[i].type;
	if (tokens[i + 1].type == IDENT && pre_type == GT)
	{
		cmds->pipes[pipe_i].in_file = tokens[i + 1].literal;
		tokens[i + 1].valid = false;
		cmds->pipes[pipe_i].option_fd_in = tokens[i].option_fd;
		if (access(tokens[i + 1].literal, F_OK | R_OK) != 0)
		{
			perror(tokens[i + 1].literal);
			rval = false;
		}
	}
	else if (pre_type == D_GT && is_string_token(tokens[i + 1].type))
	{
		tokens[i + 1].valid = false;
		cmds->pipes[pipe_i].option_fd_in = tokens[i].option_fd;
		cmds->pipes[pipe_i].heredoc_fd = tokens[i].heredoc_fd;
	}
	return (rval);
}

int	change_std_out(t_cmds *cmds, t_token *tokens, size_t i, size_t pipe_i)
{
	int	rval;
	int	pre_type;

	rval = true;
	pre_type = tokens[i].type;
	if (tokens[i + 1].type == IDENT && pre_type == LT)
	{
		cmds->pipes[pipe_i].out_file = tokens[i + 1].literal;
		unlink(cmds->pipes[pipe_i].out_file);
		rval = create_file(cmds->pipes[pipe_i].out_file, O_WRONLY | O_CREAT);
		cmds->pipes[pipe_i].write_option = O_WRONLY;
		tokens[i + 1].valid = false;
		cmds->pipes[pipe_i].option_fd_out = tokens[i].option_fd;
	}
	else if (tokens[i + 1].type == IDENT && pre_type == D_LT)
	{
		cmds->pipes[pipe_i].out_file = tokens[i + 1].literal;
		rval = create_file(cmds->pipes[pipe_i].out_file, O_WRONLY | O_APPEND);
		cmds->pipes[pipe_i].write_option = O_WRONLY | O_APPEND;
		tokens[i + 1].valid = false;
		cmds->pipes[pipe_i].option_fd_out = tokens[i].option_fd;
	}
	return (rval);
}

int	search_std_in_and_out(t_token *tokens, t_cmds *cmds, size_t i)
{
	size_t	ci;
	size_t	pipe_i;
	int		rval;

	i = 0;
	ci = 0;
	pipe_i = 0;
	rval = true;
	while (tokens[i].type != EOS)
	{
		if ((!tokens[i].valid || !rval) && ++i)
			continue ;
		if ((tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND) && ++ci)
			pipe_i = 0;
		else if (tokens[i].type == PIPE)
			pipe_i++;
		else if (tokens[i].type == GLT)
			rval = change_std_glt(&(cmds[ci]), tokens, i, pipe_i);
		else if (tokens[i].type == GT || tokens[i].type == D_GT)
			rval = change_std_in(&(cmds[ci]), tokens, i, pipe_i);
		else if (tokens[i].type == LT || tokens[i].type == D_LT)
			rval = change_std_out(&(cmds[ci]), tokens, i, pipe_i);
		i++;
	}
	return (rval);
}
