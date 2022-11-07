/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:51:15 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/07 16:37:11 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exit_status.h"
#include "signal_minishell.h"

static void	handle_heredoc_signal(int sig)
{
	extern sig_atomic_t	g_signal_flag;

	if (sig == SIGINT)
	{
		g_signal_flag = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_heredoc_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc_signal);
}

int	signal_check_state(void)
{
	if (g_signal_flag)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}
