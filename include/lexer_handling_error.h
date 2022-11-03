/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handling_error.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:10:04 by hsano             #+#    #+#             */
/*   Updated: 2022/11/02 14:12:59 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HANDLING_ERROR_H
#define LEXER_HANDLING_ERROR_H
#include "lexer.h"
#include "lexer_util.h"
#include "lexer_util.h"
#include "kill_myprocess.h"
#include "stdbool.h"
t_token	*lexer_handling_error(t_token *tokens);
#endif
