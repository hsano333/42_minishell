/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_asterisk_saved_file.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:52:25 by hsano             #+#    #+#             */
/*   Updated: 2022/10/18 16:28:36 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand.h"

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

	return (finded_file_func(GET_AST_FINDED_FILE, NULL, &tmp, &tmp));
}


void	set_finded_file(char *added_file)
{
	char	*saved_filename;
	char	*tmp_malloc;
	size_t	used;
	size_t	max;
	size_t	added_len;

	saved_filename = finded_file_func(GET_AST_FINDED_FILE, NULL, &used, &max);
	added_len = ft_strlen(added_file);
	//printf("set_finded_file No.3 added_len=%zu, max - used=%zu\n", added_len, max - used);
	if (added_len > (max - used) * 0.75 || saved_filename == NULL)
	{
		max = max + PATH_MAX * 4;
		tmp_malloc = malloc(max);
		if (!tmp_malloc)
			return ;
		if (saved_filename )
			ft_strlcpy(tmp_malloc, saved_filename ,max);
		free(saved_filename);
		saved_filename = tmp_malloc;
	}
	ft_strlcat(saved_filename, " ", max);
	ft_strlcat(saved_filename, added_file, max);
	used = ft_strlen(saved_filename);
	finded_file_func(SET_AST_FINDED_FILE, saved_filename, &used, &max);
}

void	clear_finded_file(void)
{
	size_t	tmp;

	finded_file_func(CLEAR_AST_FINDED_FILE, NULL, &tmp, &tmp);
}
