/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_myprocess.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:10:43 by hsano             #+#    #+#             */
/*   Updated: 2022/11/04 05:10:58 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KILL_MYPROCESS_H
# define KILL_MYPROCESS_H
# include "minishell.h"
# include "lexer_util.h"
# include "parser_util.h"
# include <errno.h>

void	kill_myprocess(int no, char *message1, t_token *tokens, t_cmds *cmds);
#endif
