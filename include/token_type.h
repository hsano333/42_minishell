/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:16:07 by hsano             #+#    #+#             */
/*   Updated: 2022/11/19 02:25:23 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_TYPE_H
# define TOKEN_TYPE_H
# include "lexer.h"

int	is_begin_error_token(t_token_type type);
int	is_string_token(t_token_type type);
int	is_token_must_next_string(t_token_type type);
int	is_connection_token(t_token_type type);
int	is_rparen_left_valid_token(t_token_type type);
int	is_quote_token(t_token_type type);
int	not_if_token(t_token_type type);
#endif
