/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:22:58 by hsano             #+#    #+#             */
/*   Updated: 2022/11/06 22:44:34 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MINISHELL_H
# define SIGNAL_MINISHELL_H

void	handle_global_signals(void);
void	handle_cmd_signals(void);
void	handle_heredoc_signals(void);
#endif
