/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_asterisk_util.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:41:20 by hsano             #+#    #+#             */
/*   Updated: 2022/11/29 00:12:07 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand.h"
#include "parser_find_cmds_util.h"
#include "libft_str.h"
#include "env.h"

t_ast_end_mode	is_equal_or_asterisk(char *ast_word, char *filename)
{
	size_t	i;

	i = 0;
	while (filename[i] && ast_word[i])
	{
		if (filename[i] != ast_word[i] && ast_word[i] == '*' )
		{
			if (ast_word[i + 1] == '/')
				return (NEXT_DIR);
			return (NEXT_ASTERISK);
		}
		else if (filename[i] != ast_word[i])
			return (FALSE_END);
		i++;
	}
	if (!filename[i] && ast_word[i] == '/')
		return (NEXT_DIR);
	if (filename[i] == ast_word[i])
		return (TRUE_END);
	return (FALSE_END);
}

static int	get_prefix_dir_common(char *p_slash \
		, char *str, char *filename, size_t *i)
{
	char	*path;

	if (p_slash == NULL)
	{
		path = get_env_val("PWD");
		ft_strlcpy(filename, path, PATH_MAX + 1);
		free(path);
		return (true);
	}
	else if (str[0] == '/')
	{
		p_slash[0] = '\0';
		ft_strlcpy(filename, str, PATH_MAX + 1);
		*i = (size_t)(p_slash - str) + 1;
		p_slash[0] = '/';
		return (true);
	}
	return (false);
}

void	get_prefix_dir(char *str, char *filename, size_t *i)
{
	char	*p_ast;
	char	*p_slash;
	char	*path;

	p_ast = ft_strchr(str, '*');
	p_ast[0] = '\0';
	p_slash = ft_strrchr(str, '/');
	p_ast[0] = '*';
	*i = 0;
	if (get_prefix_dir_common(p_slash, str, filename, i))
		return ;
	path = get_env_val("PWD");
	ft_strlcpy(filename, path, PATH_MAX + 1);
	ft_strlcat(filename, "/", PATH_MAX + 1);
	p_slash[0] = '\0';
	ft_strlcat(filename, str, PATH_MAX + 1);
	*i = (size_t)(p_slash - str) + 1;
	p_slash[0] = '/';
	free(path);
}

void	add_expanding_asterisk_str(char *dst, char *src \
		, size_t max, int is_absolute)
{
	char	*pwd_str;
	size_t	len;

	pwd_str = get_env_val("PWD");
	if (!pwd_str)
	{
		paraser_expand_asterisk_error(SET_AST_ERROR);
		return ;
	}
	if (is_absolute)
		ft_strlcat(dst, src, max);
	else
	{
		len = ft_strlen(pwd_str);
		ft_strlcat(dst, &src[len + 1], max);
	}
	len = ft_strlen(dst);
	dst[len] = PARSER_DELIMITER;
	dst[len + 1] = '\0';
	free(pwd_str);
}

int	delete_consecutive_ast(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '*' && str[i + 1] == '*')
		{
			ft_memmove(&(str[i]), &(str[i + 1]), len - i);
			i--;
		}
		i++;
	}
	return (true);
}
