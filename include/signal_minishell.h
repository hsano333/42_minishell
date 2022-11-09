/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:22:58 by hsano             #+#    #+#             */
/*   Updated: 2022/11/07 16:37:18 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MINISHELL_H
# define SIGNAL_MINISHELL_H
# include <signal.h>
# include "signal_flag.h" 

sig_atomic_t	g_signal_flag;

void	handle_global_signals(void);
void	handle_cmd_signals(void);
void	handle_heredoc_signals(void);
int		signal_check_state(void);
#endif
