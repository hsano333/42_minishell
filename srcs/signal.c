/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:51:15 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/20 03:29:11 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exit_status.h"
#include "signal_minishell.h"

static void	handle_cmd_signal(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		set_exit_status(130);
		rl_replace_line("", 0);
	}
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
