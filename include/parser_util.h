/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:49:35 by hsano             #+#    #+#             */
/*   Updated: 2022/10/22 15:21:18 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTIL_H
# define PARSER_UTIL_H

int	is_error_cmds(t_cmds *cmds);
void	clear_all_cmds(t_cmds **cmds);
#endif
