/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_asterisk_saved_file.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:52:25 by hsano             #+#    #+#             */
/*   Updated: 2022/10/29 03:32:08 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand.h"

int	paraser_expand_asterisk_error(t_ast_fined_file_mode mode)
{
	static int	error = false;

	if (mode == SET_AST_ERROR)
		error = true;
	else if (mode == GET_AST_ERROR)
		return (error);
	return (true);
}

static char	*finded_file_func(t_ast_fined_file_mode mode, char *finded_file, size_t *used, size_t *max)
{
	static char	*finded_file_p = NULL;
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

	if (paraser_expand_asterisk_error(GET_AST_ERROR))
		return (NULL);
	return (finded_file_func(GET_AST_FINDED_FILE, NULL, &tmp, &tmp));
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
		tmp_malloc = malloc(max);
		if (!tmp_malloc && paraser_expand_asterisk_error(SET_AST_ERROR))
			return ;
		if (saved_filename )
			ft_strlcpy(tmp_malloc, saved_filename ,max);
		free(saved_filename);
		saved_filename = tmp_malloc;
	}
	//ft_strlcat(saved_filename, " ", max);
	//ft_strlcat(saved_filename, added_file, max);
	add_expanding_asterisk_str(saved_filename, added_file, max, is_absolute);
	used = ft_strlen(saved_filename);
	finded_file_func(SET_AST_FINDED_FILE, saved_filename, &used, &max);
}

void	clear_finded_file(void)
{
	size_t	tmp;

	finded_file_func(CLEAR_AST_FINDED_FILE, NULL, &tmp, &tmp);
}
