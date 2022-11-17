/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:06:00 by hsano             #+#    #+#             */
/*   Updated: 2022/11/18 02:34:10 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERROR_H
# define PARSER_ERROR_H
# include "parser.h"

typedef enum e_acs_mode
{
	GET,
	SET,
}	t_acs_mode;

int	set_parser_error(int error);
int	get_parser_error(void);
int	parser_error(int no, t_cmds *cmds);
#endif
