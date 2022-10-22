/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_change_std.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:52:31 by hsano             #+#    #+#             */
/*   Updated: 2022/10/23 02:48:03 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parser_std.h"
#include "parser_heredoc.h"

#include <stdio.h>

static int	create_file(char *filename, int option)
{
	int		fd_out;

	fd_out = open(filename, option, 0744);
	if (fd_out < 0 && option == (O_APPEND | O_WRONLY))
	{
		option = O_CREAT | O_WRONLY ;
		fd_out = open(filename, option, 0777);
		if (fd_out < 0)
			return (false);
	}
	else if (fd_out < 0)
		return (false);
	close(fd_out);
	return (true);
}

int	change_std_in(t_cmds *cmds, t_token *tokens, size_t i, size_t pipe_i)
{
	int	rval;

	rval = true;
	if (tokens[i + 1].type == IDENT)
	{
		//cmds->in = SAVED_FILE;
		if (tokens[i].type == GT)
		{
			cmds->pipes[pipe_i].in_file = tokens[i + 1].literal;
			tokens[i + 1].valid = false;
		}
		else if (tokens[i].type == D_GT)
		{
			//cmds->hiredoc_eos = tokens[i + 1].literal;
			cmds->pipes[pipe_i].in_file = HEREDODC_FILE;
			tokens[i + 1].valid = false;
		}
	}
	//else
		//cmds->in = ERROR;
	return (rval);
}

int	change_std_out(t_cmds *cmds, t_token *tokens, size_t i, size_t pipe_i)
{
	int	rval;

	if (tokens[i + 1].type == IDENT)
	{
		cmds->pipes[pipe_i].out_file = tokens[i + 1].literal;
		if (tokens[i].type == LT)
		{
			rval = false;
			//cmds->pipes->pipe[pipe_i].out_file = NULL;
			//cmds->pipes->pipe[pipe_i].->out = STD_OUT;
			rval = create_file(cmds->pipes[pipe_i].out_file, O_WRONLY | O_CREAT);
			tokens[i + 1].valid = false;
		}
		else if (tokens[i].type == D_LT)
		{
			rval = false;
			//cmds->pipes->pipe[pipe_i].out = STD_OUT_APPEND;
			rval = create_file(cmds->pipes[pipe_i].out_file, O_WRONLY | O_APPEND);
			tokens[i + 1].valid = false;
		}
	}
	//if (!rval)
		//cmds->out = ERROR;
	return (rval);
}


void	search_std_in_and_out(t_token *tokens, t_cmds *cmds)
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
		if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND)
			cmd_i++;
		else if (tokens[i].type == PIPE)
			pipe_i++;
		if (tokens[i].type == GT || tokens[i].type == D_GT)
			change_std_in(&(cmds[cmd_i]), tokens, i, pipe_i);
		else if (tokens[i].type == LT || tokens[i].type == D_LT)
			change_std_out(&(cmds[cmd_i]), tokens, i, pipe_i);
		i++;
	}
}
