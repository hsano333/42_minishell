/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_doller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:16 by hsano             #+#    #+#             */
/*   Updated: 2022/10/19 00:08:58 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parser.h"
#include "libft_str.h"
#include "minishell.h"
#include "lexer_util.h"

static void	expand_recursive(char *str, token_type pre_token, char **dst_str);

static int	is_valid_env_char(char c)
{
	if (ft_isalnum(c))
		return (true);
	else if (c == '_')
		return (true);
	return (false);

}

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

static void expand(char *str, char **dst_str, size_t i)
{
	char	*env_str;
	size_t	j;
	char	tmp;

	j = 0;
	while (is_valid_env_char(str[j]))
			j++;
	tmp = str[j];
	str[j] = '\0';
	env_str = env_func(NULL, GET_ENV, str, NULL);
	str[j] = tmp;
	printf("str=%s, env_str=%s\n", str, env_str);
	*dst_str = join_and_free_str(*dst_str, env_str, ft_strlen(env_str), true);
	if (str[i] == '$' && is_valid_env_char(str[i + 1]))
		expand_recursive(&(str[i + 1]), DOLLER, dst_str);
	else if (str[i])
		expand_recursive(&(str[i]), NON, dst_str);

}

static void	expand_recursive(char *str, token_type pre_token, char **dst_str)
{
	size_t	i;

	i = 0;
	while (str[i] && is_valid_env_char(str[i]))
		i++;
	if (pre_token == DOLLER && i > 0)
		expand(str, dst_str, i);
	else if(str[i] == '$' && is_valid_env_char(str[i + 1]))
	{
		*dst_str = join_and_free_str(*dst_str, str, i, false);
		expand_recursive(&(str[i + 1]), DOLLER, dst_str);
	}
	else if (str[i])
	{
			*dst_str = join_and_free_str(*dst_str, str, i + 1, false);
			expand_recursive(&(str[i + 1]), NON, dst_str);
	}
}

void	expand_doller(t_token *token, token_type pre_token)
{
	char	*dst_str;

	if (pre_token == SINGLE_QUOTE)
		return ;
	if (DOLLER != (token->type & DOLLER))
		return ;
	dst_str = ft_strdup("");
	expand_recursive(token->literal, NON, &dst_str);
	if (!dst_str)
		token->error = true;
	token->literal = dst_str;
	//if (DOLLER == (token->type & DOLLER))
		//expand_asterisk(token, pre_token);
}
