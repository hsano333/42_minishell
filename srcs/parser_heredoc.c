/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:54:48 by hsano             #+#    #+#             */
/*   Updated: 2022/11/06 22:20:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_heredoc.h"
//#include "signal_minishell.h"
#include "exit_status.h"

sig_atomic_t	g_signal_flag;

static int	check_state(void)
{
	if (g_signal_flag)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}

static int	execute_heredoc_loop(t_heredoc *heredoc, int fd, int error)
{
	char	*line;

	while (true)
	{
		line = readline("\033[31mheredoc> \033[0m");
		if (!line)
		{
			error = true;
			break ;
		}
		if (*line == '\0' && g_signal_flag)
		{
			g_signal_flag = 0;
			error = true;
			set_exit_status(1);
			break ;
		}
		if (ft_strncmp(line, heredoc->limiter, ft_strlen(heredoc->limiter) + 1) \
				== 0)
			break ;
		ft_putendl_fd(line, fd);
	}
	return (error);
}

static int	execute_heredoc(t_heredoc *heredoc)
{
	int		fd;
	int		error;

	rl_event_hook = check_state;
	handle_heredoc_signals();
	unlink(HEREDODC_FILE);
	fd = open(HEREDODC_FILE, O_CREAT | O_WRONLY, 0744);
	if (fd < 0)
		return (false);
	error = false;
	error = execute_heredoc_loop(heredoc, fd, error);
	close(fd);
	handle_global_signals();
	return (!error);
}

static void	get_heredoc_setting(t_heredoc *heredoc, t_token *tokens, size_t i)
{
	heredoc->valid = false;
	if (tokens[i + 1].type == IDENT)
	{
		if (tokens[i + 1].literal)
		{
			heredoc->limiter = tokens[i + 1].literal;
			heredoc->valid = true;
		}
	}
}

int	create_heredoc_file(t_token *tokens)
{
	size_t		i;
	t_heredoc	heredoc;

	i = 0;
	while (tokens[i].type != EOS)
	{
		if (!tokens[i].valid)
		{
			i++;
			continue ;
		}
		if (tokens[i].type == D_GT)
		{
			get_heredoc_setting(&heredoc, tokens, i);
			handle_global_signals();
			if (heredoc.valid)
				heredoc.valid = execute_heredoc(&heredoc);
			handle_cmd_signals();
		}
		i++;
	}
	return (heredoc.valid);
}
