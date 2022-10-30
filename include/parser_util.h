/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:49:35 by hsano             #+#    #+#             */
/*   Updated: 2022/10/31 01:37:03 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTIL_H
# define PARSER_UTIL_H
#include "parser.h"

int	is_error_cmds(t_cmds *cmds);
void	clear_all_cmds(t_cmds **cmds);
size_t	pass_space(t_token *toknes, size_t i);
#endif
