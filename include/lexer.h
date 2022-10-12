/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:56:01 by hsano             #+#    #+#             */
/*   Updated: 2022/10/13 03:01:50 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <unistd.h>

enum	e_token_type
{
	ILLEGAL = 1,
	EOS,
	IDENT,
	PIPE,
	D_PIPE,
	D_AMPERSAND,
	GT,
	LT,
	D_GT,
	D_LT,
	ASTERISK,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	DOLLER,
	EXIT_STATUS,
	//LPAREN,
	//RPAREN,
	//COMMA,
	//INT,
	//EQUAL,
	//SEMICOLON,
	//SLASH,
	//BACK_SLASH,
	//DOT,
	//D_DOT,
	NON,
};
typedef enum e_token_type token_type;

typedef struct s_token
{
	token_type	type;
	char		*literal;
	size_t		len;
	size_t		id;
	int		valid;
}	t_token;


t_token	*lexer(char *str);
size_t	expand_str(t_token *tokens, token_type pre_token, size_t i);
#endif
