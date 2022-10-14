/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:54:44 by hsano             #+#    #+#             */
/*   Updated: 2022/10/14 04:09:07 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_util.h"
#include "lexer.h"

int	is_whitespace(char c)
{
	if (c == ' ' || (0x09 <= c && c <= 0x0D))
		return (true);
	return (false);
}

size_t	whitespace_len(char *str)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			cnt++;
		i++;
	}
	return (cnt);
}

size_t token_len_helper(token_type type)
{
	if (type == D_PIPE || type == D_AMPERSAND || type == D_LT \
			|| type == D_GT || type == EXIT_STATUS)
		return (2);
	return (1);
}

t_token	*check_error(t_token *tokens)
{
	int	err;
	size_t	i;
	//t_deque	*queue;
	//t_token *tmp_token;
	
	err = false;
	i = 0;
	//queue = search_nil(tokens);
	while (tokens[i].type != EOS)
	{
		//tmp_token = ((t_deque *)(queue->next))->content;
		//if (tmp_token->type == EOS)
			//break ;
		if (tokens[i].literal == NULL)
		{
			err = true;
			break ;
		}
		i++;
	}
	if (err)
	{
		clear_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}

void	clear_tokens(t_token *tokens)
{
	size_t	i;
	
	i = 0;
	while (tokens[i].type != EOS)
	{
		free(tokens[i].literal);
		i++;
	}
	free(tokens);

}

void	put_tokens(t_token *tokens)
{
	size_t	i;
	t_token	*tmp_token;
	
	i = 0;
	while (tokens[i].type != EOS)
	{
		tmp_token = &(tokens[i]);
		if (tmp_token->valid)
			printf("id=%zu,type=%d, len=%zu str=[%s], valid=%d\n ", tmp_token->id, tmp_token->type, tmp_token->len, tmp_token->literal, tmp_token->valid);
		i++;
	}
}
