/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_valid_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 02:25:12 by hsano             #+#    #+#             */
/*   Updated: 2022/11/29 03:14:37 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_check_valid_file.h"
#include "libft_put.h"
#include <stdio.h>

int	parser_check_valid_file(t_token *token)
{
	int	rval;

	rval = true;
	if (token->expand)
	{
		if (ft_strchr(token->literal, PARSER_DELIMITER))
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			rval = false;
			token->type = NON;
		}
	}
	return (rval);
}
