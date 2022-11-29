/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:04:19 by hsano             #+#    #+#             */
/*   Updated: 2022/11/29 14:20:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_error.h"
#include "parser_util.h"
#include <stdbool.h>
#include <errno.h>

static int	static_parser_error(int mode, int flag)
{
	static int	error = false;

	if (mode == GET)
		return (error);
	else if (mode == SET)
		error = flag;
	return (error);
}

int	set_parser_error(int error)
{
	static_parser_error(SET, error);
	return (true);
}

int	get_parser_error(void)
{
	return (static_parser_error(GET, false));
}

int	parser_error(int no, t_cmds *cmds)
{
	if (no > 0)
	{
		errno = no;
		perror("minishell");
	}
	if (cmds)
		clear_all_cmds(&cmds);
	return (true);
}
