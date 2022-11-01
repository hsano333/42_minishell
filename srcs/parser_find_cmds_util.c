/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_cmds_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:37:25 by hsano             #+#    #+#             */
/*   Updated: 2022/10/29 16:31:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_find_cmds_util.h"

size_t	cnt_parser_cmd_param(t_token *token)
{
	size_t	cnt;
	size_t	len;
	char	*p;

	cnt = 1;
	if (!token->expand)
		return (cnt);
	len = ft_strlen(token->literal);
	p = ft_strnstr(token->literal + 1, " ", len);
	while (p)
	{
		cnt++;
		p = ft_strnstr(p + 1, " ", len);
	}
	return (cnt);
}
