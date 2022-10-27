/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_exit_status.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:35 by hsano             #+#    #+#             */
/*   Updated: 2022/10/27 16:34:55 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "lexer.h"
#include <stdio.h>

static	size_t	expanded_str_len(char *str, char *e_status)
{
	size_t	len;
	int	len_status;
	//char	e_status[20];
	char	*base_p;

	get_exit_status_str(e_status);
	len_status = ft_strlen(e_status) - 2;
	len = ft_strlen(str);
	base_p = ft_strnstr(str, "$?", 2);
	while (base_p)
	{
		len += len_status;
		base_p += 2;
		base_p = ft_strnstr(base_p, "$?", 2);
		if (!base_p)
			break ;
	}
	return (len);
}

static void	expand(t_token *token, char *str, size_t len, char *e_status)
{
	char	*p_doller;
	char	*backup;

	backup = token->literal;
	p_doller = ft_strnstr(token->literal, "$?", ft_strlen(token->literal));
	while (p_doller)
	{
		p_doller[0] = '\0';
		ft_strlcat(str, token->literal, len + 1);
		ft_strlcat(str, e_status, len + 1);
		token->literal = p_doller += 2;
		p_doller = ft_strnstr(token->literal, "$?", 2);
	}
	ft_strlcat(str, token->literal, len + 1);
	free(backup);
	token->literal = str;
	token->type = IDENT;
}

int	expand_exit_status(t_token *token)
{
	size_t	len;
	char	e_status[20];
	char	*str;

	if (EXIT_STATUS != (token->type & EXIT_STATUS))
		return (true);
	get_exit_status_str(e_status);
	len = expanded_str_len(token->literal, e_status);
	str = (char *)malloc(len + 1);
	str[0] = '\0';
	str[len] = '\0';
	if (!str)
		return (false);
	expand(token, str, len, e_status);
	return (true);
}
