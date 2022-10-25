/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_doller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:16 by hsano             #+#    #+#             */
/*   Updated: 2022/10/15 02:32:30 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parser.h"
#include "libft_str.h"
#include "minishell.h"
#include "lexer_util.h"

static char	*join_and_free_str(char *dst, char *str, int i, int is_free_str)
{
	char	*concat_str;
	char	tmp;

	if (!dst)
		return (NULL);
	tmp = str[i];
	str[i] = '\0';
	concat_str = ft_strjoin(dst, str);
	str[i] = tmp;
	free(dst);
	if (is_free_str)
		free(str);
	dst = NULL;
	str = NULL;
	return (concat_str);
}

void	expand_doller_recursive(char *str, token_type pre_token, char **dst_str)
{
	size_t	i;
	char	*env_str;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (pre_token == DOLLER && i > 0)
	{
		env_str = env_func(NULL, GET_ENV, str, NULL);
		*dst_str = join_and_free_str(*dst_str, env_str, ft_strlen(env_str), true);
		if (str[i] == '$' && ft_isalnum(str[i + 1]))
			expand_doller_recursive(&(str[i + 1]), DOLLER, dst_str);
		else if (str[i])
			expand_doller_recursive(&(str[i]), NON, dst_str);
	}
	else if(str[i] == '$' && ft_isalnum(str[i + 1]))
	{
		*dst_str = join_and_free_str(*dst_str, str, i, false);
		expand_doller_recursive(&(str[i + 1]), DOLLER, dst_str);
	}
	else if (str[i])
	{
			*dst_str = join_and_free_str(*dst_str, str, i + 1, false);
			expand_doller_recursive(&(str[i + 1]), NON, dst_str);
	}
}

void	expand_doller(t_token *token, token_type pre_token)
{

	char	*dst_str;

	if (pre_token == SINGLE_QUOTE)
		return ;
	dst_str = ft_strdup("");
	expand_doller_recursive(token->literal, NON, &dst_str);
	if (!dst_str)
		token->error = true;
	token->literal = dst_str;
}