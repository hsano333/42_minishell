/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_valid_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 02:25:12 by hsano             #+#    #+#             */
/*   Updated: 2022/11/30 02:02:54 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_check_valid_file.h"
#include "libft_put.h"
#include "exit_status.h"
#include <stdio.h>

int	parser_check_valid_file(t_token *token)
{
	int	rval;

	rval = true;
	if (token->expand)
	{
		if (ft_strchr(token->literal, PARSER_DELIMITER))
		{
			set_exit_status(258);
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			rval = false;
			token->type = NON;
		}
	}
	return (rval);
}
