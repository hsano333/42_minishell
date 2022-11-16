/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parenthesis.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:59:40 by hsano             #+#    #+#             */
/*   Updated: 2022/11/16 19:47:16 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_PARENTHESIS_H
# define TOKEN_PARENTHESIS_H
# include "lexer.h"
# include "parser.h"

size_t	set_paren(t_token *tokens, t_cmds *cmds, size_t i, size_t pi);
int	enable_paren_token(t_pipe *pipe);
int	have_paren_error(t_token *tokens);
#endif
