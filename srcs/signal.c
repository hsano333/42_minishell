/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:51:15 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/29 21:37:18 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exit_status.h"
#include "signal_minishell.h"

static void	handle_cmd_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		set_exit_status(130);
		rl_replace_line("", 0);
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		set_exit_status(130);
		rl_replace_line("", 0);
	}
}

void	handle_ign_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

static void	handle_global_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		set_exit_status(1);
		rl_redisplay();
	}
}

void	handle_cmd_signals(void)
{
	signal(SIGQUIT, handle_cmd_signal);
	signal(SIGINT, handle_cmd_signal);
}

void	handle_global_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_global_signal);
}
