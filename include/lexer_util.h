/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 01:08:20 by hsano             #+#    #+#             */
/*   Updated: 2022/10/27 16:21:44 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTIL_H
# define LEXER_UTIL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"
#include "libft_str.h"
#include <stdio.h>

int		is_whitespace(char c);
size_t	whitespace_len(char *str);
size_t	token_len_helper(token_type type);
t_token	*check_lexer_error(t_token *tokens);
void	put_tokens(t_token *tokens);
void	clear_tokens(t_token *tokens);
#endif

