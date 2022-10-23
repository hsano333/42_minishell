/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_asterisk.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:16 by hsano             #+#    #+#             */
/*   Updated: 2022/10/24 03:09:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_expand.h"
#include "libft_str.h"
#include "lexer_util.h"
#include "dir.h"

int	expand_loop(char *ast_word, char *dirname, char *filename);
t_ast_end_mode	is_matched_file_suffix(char *ast_word, char *dirname, char *filename);
t_ast_end_mode	is_matched_file_prefix(char *ast_word, char *dirname, char *filename);

t_ast_end_mode	is_matched_file_prefix(char *ast_word, char *dirname, char *filename)
{
	size_t	i;
	t_ast_end_mode	rval;

	i = 0;
	while (filename[i] || ast_word[i])
	{
		if (filename[i] != ast_word[i] && ast_word[i] == '*' )
		{
			if (ast_word[i + 1] == '/')
			{
				ft_strlcat(dirname,filename, PATH_MAX + 1);
				return (expand_loop(&(ast_word[i + 2]), dirname, filename));
			}
			else if (ast_word[i + 1] == '\0')
				return (true);
			else 
			{
				rval = is_matched_file_suffix(&(ast_word[i + 1]), dirname, &(filename[i]));
				if (rval == NEXT_DIR)
				{

					ft_strlcat(dirname, filename, PATH_MAX + 1);
					return ( expand_loop((char *)(ft_strchr(ast_word, '/') + 1), dirname, filename));
				}
				else
					return (rval);

			}
		}
		else if (filename[i] != ast_word[i])
			return (false);
		if (!filename[i] || !ast_word[i])
			break ;
		i++;
	}
	if (filename[i] == '\0' && ast_word[i] == '\0')
		return (TRUE_END);
	return (FALSE_END);
}

t_ast_end_mode	is_matched_file_suffix(char *ast_word, char *dirname, char *filename)
{
	size_t	i;
	t_ast_end_mode	rval;

	i = 0;
	while (filename[i] || ast_word[i])
	{
		ft_strlen(filename);
		if (ast_word[0] == filename[i])
		{
			rval = is_equal_or_asterisk(ast_word, &(filename[i]));
			if (rval == TRUE_END)
				return (TRUE_END);
			else if (rval == NEXT_ASTERISK)
				rval = is_matched_file_prefix(&(ast_word[1]), dirname, &(filename[i + 1]));
			else if (rval == NEXT_DIR)
				return (NEXT_DIR);
			if (rval != FALSE_END)
				return (rval);
		}
		if (!filename[i])
			break ;
		i++;
	}
	return (FALSE_END);
}

int	expand_loop(char *ast_word, char *dirname, char *filename)
{
	struct dirent	*ent;
	DIR	*dir;
	size_t	len;

	dir = opendir(dirname);
	if (!dir)
		return (false);
	ft_strlcat(dirname, "/", PATH_MAX + 1);
	ent = readdir(dir);
	while (ent)
	{
		ft_strlcpy(filename ,ent->d_name, PATH_MAX + 1);
		if (ft_strncmp(filename , ".", 2) == 0 || ft_strncmp(filename , "..", 3) == 0)
			len = 0;
		else if (is_matched_file_prefix(ast_word, dirname, filename) == TRUE_END)
		{
			len = ft_strlen(dirname);
			ft_strlcat(dirname, filename, PATH_MAX + 1);
			set_finded_file(dirname);
			dirname[len] = '\0';
		}
		ent = readdir(dir);
	}
	return (0);
}

size_t	expand_asterisk(t_token *token, token_type pre_token)
{
	size_t	i;
	char	dir[PATH_MAX + 1];
	char	filename[PATH_MAX + 1];

	filename[0] = '\0';
	if (pre_token == SINGLE_QUOTE || !token->valid || ASTERISK != (token->type & ASTERISK))
		return (false);
	get_prefix_dir(token->literal, dir, &i);
	if (!dir[0])
		return (0);
	expand_loop(&(token->literal[i]), dir, filename);
	token->literal = ft_strdup(get_finded_file());
	token->type = IDENT;
	clear_finded_file();
	return (true);
}
