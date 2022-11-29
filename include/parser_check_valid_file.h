/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_valid_file.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 02:58:08 by hsano             #+#    #+#             */
/*   Updated: 2022/11/29 03:16:03 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CHECK_VALID_FILE_H
# define PARSER_CHECK_VALID_FILE_H
# include "lexer.h"
# include "parser_find_cmds_util.h"

int	parser_check_valid_file(t_token *token);
#endif
