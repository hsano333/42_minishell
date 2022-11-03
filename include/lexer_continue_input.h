/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_continue_input.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:54:36 by hsano             #+#    #+#             */
/*   Updated: 2022/11/04 03:36:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTINUE_INPUT_H
# define CONTINUE_INPUT_H
# include "lexer.h"
# include "lexer_util.h"
# include <stdbool.h>
# include <libft_str.h>
# include <readline/readline.h>

int		is_continue_input(t_token *tokens);
t_token	*continued_input(t_token *tokens, char **str);
#endif
