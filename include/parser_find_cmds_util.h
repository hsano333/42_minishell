/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_cmds_util.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:46:14 by hsano             #+#    #+#             */
/*   Updated: 2022/11/03 22:59:54 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_FIND_CMDS_UTIL_H
# define PARSER_FIND_CMDS_UTIL_H
# include "lexer.h"
# include "libft_str.h"
# define PARSER_DELIMITER -128

size_t	cnt_parser_cmd_param(t_token *token);
#endif

