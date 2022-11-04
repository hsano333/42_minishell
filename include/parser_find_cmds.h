/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_cmds.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:49:10 by hsano             #+#    #+#             */
/*   Updated: 2022/11/05 03:32:04 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_FIND_CMDS_H
# define PARSER_FIND_CMDS_H
# include "parser.h"
# include "libft_str.h"

int	search_cmds_and_arg(t_token *tokens, t_cmds *cmds, size_t i);
#endif
