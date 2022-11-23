/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_asterisk.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:16 by hsano             #+#    #+#             */
/*   Updated: 2022/11/21 23:35:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_expand.h"
#include "libft_str.h"
#include "lexer_util.h"
#include "dir.h"

int				expand_loop(char *ast_word, char *d_name \
		, char *f_name, int is_absol);
t_ast_end_mode	is_suffix(char *ast_word, char *d_name \
		, char *f_name, int is_absol);
t_ast_end_mode	is_prefix(char *ast_word, char *d_name \
		, char *f_name, int is_absol);

static t_ast_end_mode	is_prefix_next(char *ast_word \
		, char *d_name, char *f_name, int is_absol)
{
	size_t			i;
	t_ast_end_mode	rval;

	i = 0;
	rval = CONTINUE;
	if (ast_word[i + 1] == '/')
	{
		ft_strlcat(d_name, f_name, PATH_MAX + 1);
		return (expand_loop(&(ast_word[i + 2]), d_name, f_name, is_absol));
	}
	else if (ast_word[i + 1] == '\0')
		return (true);
	else
	{
		rval = is_suffix(&(ast_word[i + 1]), d_name, &(f_name[i]), is_absol);
		if (rval == NEXT_DIR)
		{
			ft_strlcat(d_name, f_name, PATH_MAX + 1);
			return (expand_loop((char *)(ft_strchr(ast_word, '/') + 1) \
						, d_name, f_name, is_absol));
		}
		else
			return (rval);
	}
	return (rval);
}

t_ast_end_mode	is_prefix(char *ast_word, char *d_name \
		, char *f_name, int is_absol)
{
	size_t	i;

	i = 0;
	while (f_name[i] || ast_word[i])
	{
		if (f_name[i] != ast_word[i] && ast_word[i] == '*' )
		{
			return (is_prefix_next(&(ast_word[i]), d_name, f_name, is_absol));
		}
		else if (f_name[i] != ast_word[i])
			return (false);
		if (!f_name[i] || !ast_word[i])
			break ;
		i++;
	}
	if (f_name[i] == '\0' && ast_word[i] == '\0')
		return (TRUE_END);
	return (FALSE_END);
}

t_ast_end_mode	is_suffix(char *ast_word, char *d_name \
		, char *f_name, int is_absol)
{
	size_t			i;
	t_ast_end_mode	rval;

	i = 0;
	while (f_name[i] || ast_word[0])
	{
		if (ast_word[0] == f_name[i])
		{
			rval = is_equal_or_asterisk(ast_word, &(f_name[i]));
			if (rval == TRUE_END)
				return (TRUE_END);
			else if (rval == NEXT_ASTERISK)
				rval = is_prefix(&(ast_word[1]) \
						, d_name, &(f_name[i + 1]), is_absol);
			else if (rval == NEXT_DIR)
				return (NEXT_DIR);
			if (rval != FALSE_END)
				return (rval);
		}
		if (!f_name[i])
			break ;
		i++;
	}
	return (FALSE_END);
}

int	expand_loop(char *ast_word, char *d_name, char *f_name, int is_absol)
{
	struct dirent	*ent;
	DIR				*dir;
	size_t			len;

	dir = opendir(d_name);
	if (!dir)
		return (false);
	ft_strlcat(d_name, "/", PATH_MAX + 1);
	ent = readdir(dir);
	while (ent)
	{
		ft_strlcpy(f_name, ent->d_name, PATH_MAX + 1);
		if (ast_word[0] != '.' && ft_strncmp(f_name, ".", 1) == 0)
			len = 0;
		else if (is_prefix(ast_word, d_name, f_name, is_absol) == TRUE_END)
		{
			len = ft_strlen(d_name);
			ft_strlcat(d_name, f_name, PATH_MAX + 1);
			set_finded_file(d_name, is_absol);
			d_name[len] = '\0';
		}
		ent = readdir(dir);
	}
	closedir(dir);
	return (0);
}

int	expand_asterisk(t_token *token, t_token_type pre_token)
{
	size_t	i;
	char	dir[PATH_MAX + 1];
	char	f_name[PATH_MAX + 1];

	f_name[0] = '\0';
	if (pre_token == SINGLE_QUOTE || pre_token == DOUBLE_QUOTE)
		return (true);
	if (!token->valid || ASTERISK != (token->type & ASTERISK))
		return (true);
	delete_consecutive_ast(token->literal);
	get_prefix_dir(token->literal, dir, &i);
	if (!dir[0])
		return (true);
	expand_loop(&(token->literal[i]), dir, f_name, token->literal[0] == '/');
	if (paraser_expand_asterisk_error(GET_AST_ERROR))
		return (false);
	save_and_clear_finded_file(token);
	if (!token->literal)
		return (false);
	return (true);
}
