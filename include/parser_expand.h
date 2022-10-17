/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:37:23 by hsano             #+#    #+#             */
/*   Updated: 2022/10/17 23:58:23 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_EXPAND_H
# define PARSER_EXPAND_H
# include <dirent.h>
# include <limits.h>
# include "minishell.h"
# include "env.h"
enum e_ast_mode
{
	PREFIX= 0,
	SUFFIX,
};
typedef enum e_ast_mode t_ast_mode;

enum e_ast_end_mode
{
	FLASE_END,
	TRUE_END,
	NEXT_DIR,
};
typedef enum e_ast_end_mode t_ast_end_mode;

void	expand_doller(t_token *token, token_type pre_token);
size_t	expand_asterisk(t_token *tokens, token_type pre_token);
int	parser_expand(t_token *tokens);

#endif
