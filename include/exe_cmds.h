/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:58:04 by hsano             #+#    #+#             */
/*   Updated: 2022/11/16 01:47:39 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_CMDS_H
# define EXE_CMDS_H
//# include "parser.h"
# include "lexer.h"
# include "pipex.h"
# include "exit_status.h"

void	exe_cmds(t_token *tokens);
#endif
