/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_change_std.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:52:31 by hsano             #+#    #+#             */
/*   Updated: 2022/10/28 21:20:26 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parser_std.h"
#include "parser_heredoc.h"

static int	create_file(char *filename, int option)
{
	int		fd_out;

	fd_out = open(filename, option, 0744);
	if (fd_out < 0 && option == (O_APPEND | O_WRONLY))
	{
		option = O_CREAT | O_WRONLY ;
		fd_out = open(filename, option, 0744);
		if (fd_out < 0)
			return (false);
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
		if (access(tokens[i + 1].literal, F_OK) != 0)
			rval = create_file(tokens[i + 1].literal, O_WRONLY | O_CREAT);
		if (!rval)
			return (rval);
		cmds->pipes[pipe_i].out_file = NULL;
		cmds->pipes[pipe_i].in_file = tokens[i + 1].literal;
	}
	return (true);
}

int	change_std_in(t_cmds *cmds, t_token *tokens, size_t i, size_t pipe_i)
{
	int	rval;

	rval = true;
	if (tokens[i + 1].type == IDENT)
	{
		if (tokens[i].type == GT)
		{
			cmds->pipes[pipe_i].in_file = tokens[i + 1].literal;
			tokens[i + 1].valid = false;
		}
		else if (tokens[i].type == D_GT)
		{
			cmds->pipes[pipe_i].in_file = HEREDODC_FILE;
			tokens[i + 1].valid = false;
		}
	}
	return (rval);
}

int	change_std_out(t_cmds *cmds, t_token *tokens, size_t i, size_t pipe_i)
{
	int	rval;

	rval = true;
	if (tokens[i + 1].type == IDENT)
	{
		cmds->pipes[pipe_i].out_file = tokens[i + 1].literal;
		if (tokens[i].type == LT)
		{
			rval = false;
			unlink(cmds->pipes[pipe_i].out_file);
			rval = create_file(cmds->pipes[pipe_i].out_file, O_WRONLY | O_CREAT);
			cmds->pipes[pipe_i].write_option = O_WRONLY;
			tokens[i + 1].valid = false;
		}
		else if (tokens[i].type == D_LT)
		{
			rval = false;
			rval = create_file(cmds->pipes[pipe_i].out_file, O_WRONLY | O_APPEND);
			cmds->pipes[pipe_i].write_option = O_WRONLY | O_APPEND;
			tokens[i + 1].valid = false;
		}
	}
	return (rval);
}


int	search_std_in_and_out(t_token *tokens, t_cmds *cmds)
{
	size_t	i;
	size_t	cmd_i;
	size_t	pipe_i;
	int	rval;

	i = 0;
	cmd_i = 0;
	pipe_i = 0;
	rval = true;
	while (tokens[i].type != EOS)
	{
		if ((!tokens[i].valid || !rval) && ++i)
			continue ;
		if ((tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND) && cmd_i++)
			pipe_i = 0;
		else if (tokens[i].type == PIPE)
			pipe_i++;
		else if (tokens[i].type == GLT)
			rval = change_std_glt(&(cmds[cmd_i]), tokens, i, pipe_i);
		else if (tokens[i].type == GT || tokens[i].type == D_GT)
			rval = change_std_in(&(cmds[cmd_i]), tokens, i, pipe_i);
		else if (tokens[i].type == LT || tokens[i].type == D_LT)
			rval = change_std_out(&(cmds[cmd_i]), tokens, i, pipe_i);
		i++;
	}
	return (rval);
}
