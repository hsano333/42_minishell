/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:04:19 by hsano             #+#    #+#             */
/*   Updated: 2022/11/18 00:01:12 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_error.h"
#include "parser_util.h"
#include <stdbool.h>
#include <errno.h>

static int	parser_error(int mode, int flag)
{
	static int error = false;

	if (mode == GET)
		return (error);
	else if (mode == SET)
		error = flag;
	return (error);
}

int	set_parser_error(int error)
{
	parser_error(SET, error);
	return (true);
}

int	get_parser_error(void)
{
	return (parser_error(GET, false));
}

int	handling_parser_error(int no, t_cmds *cmds)
{

	errno = no;
	perror("minishell");
	clear_all_cmds(&cmds);
	return (true);
}
