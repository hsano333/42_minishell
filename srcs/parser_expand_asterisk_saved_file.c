/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_asterisk_saved_file.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:52:25 by hsano             #+#    #+#             */
/*   Updated: 2022/11/17 22:38:43 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand.h"
#include "parser_find_cmds_util.h"

int	paraser_expand_asterisk_error(t_ast_fined_file_mode mode)
{
	static int	error = false;

	if (mode == SET_AST_ERROR)
		error = true;
	else if (mode == GET_AST_ERROR)
		return (error);
	return (true);
}

static char	*finded_file_func(t_ast_fined_file_mode mode, char *finded_file \
		, size_t *used, size_t *max)
{
	static char		*finded_file_p = NULL;
	static size_t	cur_used = 0;
	static size_t	cur_max = 0;

	if (mode == GET_AST_FINDED_FILE)
	{
		*used = cur_used;
		*max = cur_max;
		return (finded_file_p);
	}
	else if (mode == SET_AST_FINDED_FILE)
	{
		finded_file_p = finded_file;
		cur_max = *max;
		cur_used = *used;
	}
	else if (mode == CLEAR_AST_FINDED_FILE)
	{
		free(finded_file_p);
		finded_file_p = NULL;
	}
	return (NULL);
}

char	*get_finded_file(void)
{
	size_t	tmp;
	size_t	len;
	char	*str;

	if (paraser_expand_asterisk_error(GET_AST_ERROR))
		return (NULL);
	str = finded_file_func(GET_AST_FINDED_FILE, NULL, &tmp, &tmp);
	len = ft_strlen(str);
	if (len > 0)
	{
		if (str[len - 1] == PARSER_DELIMITER)
			str[len - 1] = '\0';
	}
	return (str);
}

void	set_finded_file(char *added_file, int is_absolute)
{
	char	*saved_filename;
	char	*tmp_malloc;
	size_t	used;
	size_t	max;
	size_t	added_len;

	saved_filename = finded_file_func(GET_AST_FINDED_FILE, NULL, &used, &max);
	added_len = ft_strlen(added_file);
	if (added_len > (max - used) * 0.75 || saved_filename == NULL)
	{
		max = max + PATH_MAX * 4;
		tmp_malloc = ft_calloc(max, 1);
		if (tmp_malloc  && saved_filename)
			ft_strlcpy(tmp_malloc, saved_filename, max);
		free(saved_filename);
		saved_filename = tmp_malloc;
		if (!tmp_malloc && paraser_expand_asterisk_error(SET_AST_ERROR))
			return ;
	}
	add_expanding_asterisk_str(saved_filename, added_file, max, is_absolute);
	used = ft_strlen(saved_filename);
	finded_file_func(SET_AST_FINDED_FILE, saved_filename, &used, &max);
}

void	save_and_clear_finded_file(t_token *token)
{
	size_t	tmp;
	char	*tmp_str;

	token->type = IDENT;
	token->expand = true;
	tmp_str = get_finded_file();
	if (tmp_str)
	{
		free(token->literal);
		token->literal = ft_strdup(tmp_str);
		if (!token->literal)
			paraser_expand_asterisk_error(SET_AST_ERROR);
	}
	finded_file_func(CLEAR_AST_FINDED_FILE, NULL, &tmp, &tmp);
}
