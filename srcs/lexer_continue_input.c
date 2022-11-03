/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_continue_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:49:41 by hsano             #+#    #+#             */
/*   Updated: 2022/11/04 05:06:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_continue_input.h"

static	t_token *error_process(t_token *tokens, char *line)
{
		clear_tokens(tokens);
		tokens = NULL;
		if (line)
			free(line);
		return NULL;

}

t_token	*continued_input(t_token *tokens, char **str)
{
	size_t	len;
	char	*new_str;
	char	*line;

	line = readline("\033[31m > \033[0m");
	if (!line)
		return (error_process(tokens, NULL));
	len = ft_strlen(*str) + ft_strlen(line);
	new_str = malloc(len + 1 + 1);
	if (!new_str)
		return (error_process(tokens, line));
	ft_strlcpy(new_str, *str, ft_strlen(*str) + 1);
	ft_strlcat(new_str, " ", len + 1 + 1);
	ft_strlcat(new_str, line, len + 1 + 1);
	free(*str);
	*str = new_str;
	clear_tokens(tokens);
	return (lexer(new_str));
}

int	is_continue_input(t_token *tokens)
{
	size_t					i;
	size_t					j;
	size_t					len;
	t_token_type			last_token;
	const	t_token_type	continued_token[] = {PIPE, D_PIPE, D_AMPERSAND};

	i = 0;
	len = sizeof(continued_token) / sizeof(t_token_type);
	while (tokens[i].type != EOS)
		i++;
	if (i > 0)
	{
		last_token = tokens[i - 1].type;
		j = 0;
		while (j < len)
		{
			if (last_token == continued_token[j])
				return (true);
			j++;
		}
	}
	return (false);
}
