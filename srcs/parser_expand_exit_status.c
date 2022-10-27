/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_exit_status.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:35 by hsano             #+#    #+#             */
/*   Updated: 2022/10/26 23:32:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "lexer.h"
#include <stdio.h>

static	size_t	expanded_str_len(char *str)
{
	size_t	len;
	int	len_status;
	char	e_status[20];
	char	*base_p;

	printf("expanded_str_len No.1\n");
	get_exit_status_str(e_status);
	printf("expanded_str_len No.2 exit status=%s\n", e_status);
	len_status = ft_strlen(e_status) - 2;
	printf("expanded_str_len No.3\n");
	len = ft_strlen(str);
	printf("expanded_str_len No.4\n");

	base_p = str;

	while (base_p)
	{
	printf("expanded_str_len No.5\n");
		base_p = ft_strnstr(base_p, "$?", 2);
	printf("expanded_str_len No.6\n");
		len += len_status;
		if (!base_p)
			break ;
		base_p += 1;
	}
	return (len);
}

void	expand_exit_status(t_token *token)
{
	//char	*p_doller;
	//char	*base_p;
	size_t	len;
	//char	*str;

	//base_p = token->literal;
	len = expanded_str_len(token->literal);
	printf("len=%zu\n", len);
	/*
	str = (char *)malloc(len + 1);
	if (!str)
		printf("memmory error\n");


	len = ft_strlen(token->literal) + 1;
	p_doller = token->literal;
	get_
	while (p_doller)
		p_doller = ft_strnstr(p_doller, "$?", 2);
	base_p = token->literal;
	p_doller = ft_strnstr(token->literal, "$?", 2);
	ft_substr(base_p, 0, (size_t)(p_doller - base_p));
	*/

}

