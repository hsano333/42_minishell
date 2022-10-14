/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:06:43 by hsano             #+#    #+#             */
/*   Updated: 2022/10/12 14:00:58 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;

	cmds = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	cmds[0].in = (int)(tokens[0].type);
	return (cmds);
}
