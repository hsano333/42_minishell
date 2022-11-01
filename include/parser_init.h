/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:50:32 by hsano             #+#    #+#             */
/*   Updated: 2022/10/28 16:07:45 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INIT_H
# define PARSER_INIT_H
# include "parser.h"

t_cmds	*init_parser(t_token *tokens, int *error);
#endif
