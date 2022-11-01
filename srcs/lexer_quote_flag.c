/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 03:25:37 by hsano             #+#    #+#             */
/*   Updated: 2022/10/31 04:10:39 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_quote_flag.h"
#include <stdio.h>

static token_type	lexer_quote_flag(int mode, token_type flag)
{
	static token_type quote_flag = NON;

	if (mode == LEXER_GET_FLAG)
		return (quote_flag);
	else
		quote_flag = flag;
	return (0);
}

token_type	get_lexer_quote(void)
{
	return (lexer_quote_flag(LEXER_GET_FLAG , 0));
}

void	set_lexer_quote(token_type flag)
{
	lexer_quote_flag(LEXER_SET_FLAG , flag);
}
