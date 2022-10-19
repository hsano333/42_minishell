/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_change_std.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:52:31 by hsano             #+#    #+#             */
/*   Updated: 2022/10/19 16:17:59 by hsano            ###   ########.fr       */
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
	//int		read_size;
	//int		option;
	//char	buf[READ_MAX];

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

void	change_std_in(t_cmd *cmds, t_token *tokens, size_t i)
{

	if (tokens[i + 1].type == IDENT)
	{
		cmds->in = SAVED_FILE;
		if (tokens[i].type == GT)
		{
			cmds->in_file = tokens[i + 1].literal;
		}
		else if (tokens[i].type == D_GT)
		{
			cmds->hiredoc_eos = tokens[i + 1].literal;
			cmds->in_file = HEREDODC_FILE;
			//heredoc_input();
			//heredoc is executed
		}
	}
	else
		cmds->in = ERROR;
}

void	change_std_out(t_cmd *cmds, t_token *tokens, size_t i)
{
	int	rval;

	if (i > 0 && tokens[i + 1].type == IDENT)
	{
		cmds->out_file = tokens[i + 1].literal;
		if (tokens[i].type == LT)
		{
			rval = false;
			cmds->out = STD_OUT;
			rval = create_file(cmds->out_file, O_WRONLY | O_CREAT);
			//outfile is created
		}
		else if (tokens[i].type == D_LT)
		{
			rval = false;
			cmds->out = STD_OUT_APPEND;
			rval = create_file(cmds->out_file, O_WRONLY | O_APPEND);
		}
	}
	if (!rval)
		cmds->out = ERROR;
}

void	init_cmd(t_cmd *cmd, size_t no)
{
	cmd->in = STD_IN;
	cmd->out = STD_OUT;
	cmd->in_file = NULL;
	cmd->hiredoc_eos = NULL;
	cmd->out_file = NULL;
	cmd->cmd = NULL;
	cmd->last = false;
	cmd->no = no;
}

void	search_std_in_and_out(t_token *tokens, t_cmd *cmds)
{
	size_t	i;
	size_t	cmd_i;

	i = 0;
	cmd_i = 0;
	init_cmd(&(cmds[0]), cmd_i);
	while (tokens[i].type != EOS)
	{
		if (!tokens[i].valid)
		{
			i++;
			continue ;
		}
		if (tokens[i].type == D_PIPE || tokens[i].type == D_AMPERSAND)
			init_cmd(&(cmds[0]), ++cmd_i);
		if (tokens[i].type == GT || tokens[i].type == D_GT)
			change_std_in(&(cmds[cmd_i]), tokens, i);
		else if (tokens[i].type == LT || tokens[i].type == D_LT)
			change_std_out(&(cmds[cmd_i]), tokens, i);
		i++;
	}
}
