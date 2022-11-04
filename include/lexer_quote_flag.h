/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_flag.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 03:26:39 by hsano             #+#    #+#             */
/*   Updated: 2022/11/04 05:09:47 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_QUOTE_FLAG_H
# define LEXER_QUOTE_FLAG_H
# include "lexer.h"
# define LEXER_GET_FLAG 0
# define LEXER_SET_FLAG 1

t_token_type	get_lexer_quote(void);
void			set_lexer_quote(t_token_type flag);
#endif
