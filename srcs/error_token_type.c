/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:43:57 by hsano             #+#    #+#             */
/*   Updated: 2022/11/17 16:41:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_type.h"
#include <stdio.h>

int	is_begin_error_token(t_token_type type)
{
	const t_token_type	error_token[] = {PIPE, D_PIPE, D_AMPERSAND, RPAREN};
	size_t	i;
	size_t	len;

	i = 0;
	len = sizeof(error_token) / sizeof(t_token_type);
	while (i < len)
	{
		if (type == error_token[i])
			return (true);
		i++;
	}
	return (false);
}

int	is_subshell_begin_error_token(t_token_type type)
{
	const t_token_type	error_token[] = {PIPE, D_PIPE, D_AMPERSAND, RPAREN};
	size_t	i;
	size_t	len;

	i = 0;
	len = sizeof(error_token) / sizeof(t_token_type);
	while (i < len)
	{
		if (type == error_token[i])
			return (true);
		i++;
	}
	return (false);
}
