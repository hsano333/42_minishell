/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_cmds_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:37:25 by hsano             #+#    #+#             */
/*   Updated: 2022/11/03 22:39:23 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_find_cmds_util.h"
#include "libft_mem.h"
#include <stdio.h>

size_t	cnt_parser_cmd_param(t_token *token)
{
	size_t	cnt;
	size_t	len;
	char	*p;

	cnt = 1;
	if (!token->expand)
		return (cnt);
	len = ft_strlen(token->literal);
	p = ft_memchr(token->literal, PARSER_DELIMITER, len);
	while (p)
	{
		cnt++;
		p = ft_memchr(p + 1, PARSER_DELIMITER, len - (p - token->literal + 1));
	}
	return (cnt);
}
