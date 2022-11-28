/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:37:23 by hsano             #+#    #+#             */
/*   Updated: 2022/11/29 00:03:33 by hsano            ###   ########.fr       */
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

typedef enum e_ast_mode
{
	PREFIX = 0,
	SUFFIX,
}	t_ast_mode;

typedef enum e_ast_fined_file_mode
{
	INIT_AST_FINDED_FILE = 0,
	GET_AST_FINDED_FILE,
	SET_AST_FINDED_FILE,
	CLEAR_AST_FINDED_FILE,
	SET_AST_ERROR,
	GET_AST_ERROR,
}	t_ast_fined_file_mode;

typedef enum e_ast_end_mode
{
	FALSE_END = 0,
	TRUE_END,
	NEXT_DIR,
	NEXT_ASTERISK,
	CONTINUE,
}	t_ast_end_mode;

int				expand_exit_status(t_token *token);
int				expand_doller(t_token *token, t_token_type pre_token);
int				expand_asterisk(t_token *tokens, t_token_type pre_token);
size_t			parser_expand(t_token *tokens, t_token_type pre_token, \
				size_t i);
char			*get_finded_file(void);
int				paraser_expand_asterisk_error(t_ast_fined_file_mode mode);
char			*remove_pwd_from_expanding_asterisk(char *str);
void			add_expanding_asterisk_str(char *dst, char *src, size_t max, \
				int is_absolute);
void			set_finded_file(char *added_file, int is_absolute);
void			save_and_clear_finded_file(t_token *token);
void			get_prefix_dir(char *str, char *filename, size_t *i);
int				is_valid_env_char(char c);
int				delete_consecutive_ast(char *str);
t_ast_end_mode	is_equal_or_asterisk(char *ast_word, char *filename);
#endif
