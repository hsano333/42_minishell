/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 01:08:20 by hsano             #+#    #+#             */
/*   Updated: 2022/11/14 22:38:32 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTIL_H
# define LEXER_UTIL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "lexer.h"
# include "libft_str.h"
# include "libft_isto.h"
# include <stdio.h>

size_t			token_len_helper(t_token_type type);
void			put_tokens(t_token *tokens);
void			clear_tokens(t_token *tokens);
t_token_type	identify_token(char c, char next_c);
#endif
