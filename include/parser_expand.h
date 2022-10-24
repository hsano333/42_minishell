/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:37:23 by hsano             #+#    #+#             */
/*   Updated: 2022/10/24 23:50:16 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_EXPAND_H
# define PARSER_EXPAND_H
# include <dirent.h>
# include <limits.h>
# include "minishell.h"
# include "lexer.h"
# include "libft_isto.h"
# include "env.h"
# include "parser.h"
# include "lexer_util.h"

enum e_ast_mode
{
	PREFIX = 0,
	SUFFIX,
};
typedef enum e_ast_mode t_ast_mode;

enum e_ast_fined_file_mode
{
	INIT_AST_FINDED_FILE = 0,
	GET_AST_FINDED_FILE,
	SET_AST_FINDED_FILE,
	CLEAR_AST_FINDED_FILE,
};

typedef enum e_ast_fined_file_mode t_ast_fined_file_mode;

enum e_ast_end_mode
{
	FALSE_END = 0,
	TRUE_END,
	NEXT_DIR,
	NEXT_ASTERISK,
	//ASTERISK_SLASH,
};
typedef enum e_ast_end_mode t_ast_end_mode;

void	expand_doller(t_token *token, token_type pre_token);
size_t	expand_asterisk(t_token *tokens, token_type pre_token);
int	parser_expand(t_token *tokens);

char	*get_finded_file(void);
void	set_finded_file(char *added_file);
void	clear_finded_file(void);
t_ast_end_mode	is_equal_or_asterisk(char *ast_word, char *filename);
void	get_prefix_dir(char *str, char *filename, size_t *i);
#endif
