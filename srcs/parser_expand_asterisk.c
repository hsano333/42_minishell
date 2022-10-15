/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_asterisk.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:16 by hsano             #+#    #+#             */
/*   Updated: 2022/10/16 01:02:18 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parser.h"
#include "libft_str.h"
#include "minishell.h"
#include "lexer_util.h"
#include "dir.h"
#include <dirent.h>


static DIR	*get_prefix_dir(char *str)
{
	//char	tmp;
	char	*p_ast;
	char	*p_slash;
	DIR	*dir;

	printf("str=%s\n", str);
	p_ast = ft_strchr(str, '*');
	p_ast[0] = '\0';
	p_slash = ft_strrchr(str, '/');
	printf("get prefix dir No.1, p_slash=%s\n", p_slash);
	p_ast[0] = '*';
	if (p_slash == NULL)
	{
		char *tmp = env_func(NULL, GET_ENV, "PWD", NULL);
		printf("current path?=%s\n", tmp);
		return (opendir(tmp));
	}
	printf("get prefix dir No.2\n");
	p_slash[0] = '0';
	dir = opendir(p_slash);
	p_slash[0] = '/';
	//opendir();
	//readdir();
	return (dir);

}

size_t	expand_recursive(t_token *token, size_t i)
{
	char	*p_ast;
	char	*p_slash;

	p_ast = ft_strchr(token->literal, '*');
	p_ast[0] = '\0';
	p_slash = ft_strchr(token->literal, '/');
	if (!p_slash)
		return (1);
	printf("i=%zu\n", i);

	return (0);

}

size_t	expand_asterisk(t_token *token, token_type pre_token)
{
	//size_t	i;
	struct dirent	*ent;
	DIR	*dir;

	printf("astersk No.1 token->valid=%d, token->type=%d\n", token->valid, token->type);
	if (pre_token == SINGLE_QUOTE || !token->valid || ASTERISK != (token->type & ASTERISK))
		return (false);
	printf("astersk No.2\n");
	dir = get_prefix_dir(token->literal);
	if (!dir)
		return (0);
	printf("astersk No.3, dir=%p\n", dir);
	ent = readdir(dir);
	printf("astersk No.4\n");
	while (ent)
	{

		printf("file=%s, type=%d\n", ent->d_name, ent->d_type);
		ent = readdir(dir);
	}
	printf("astersk No.5\n");
	//pre_dir = expand_recursive(token, i);
		//search_word();
	return (true);
}
