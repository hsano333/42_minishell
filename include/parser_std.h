/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_std.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:41:42 by hsano             #+#    #+#             */
/*   Updated: 2022/10/21 15:48:25 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_STD_H
# define PARSER_STD_H
# include "parser.h"
# include "lexer.h"

void	search_std_in_and_out(t_token *tokens, t_cmds *cmds);
#endif
