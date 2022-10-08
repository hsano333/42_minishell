/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:56:01 by hsano             #+#    #+#             */
/*   Updated: 2022/10/09 02:34:01 by hsano            ###   ########.fr       */
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
	SEMICOLON,
	SLASH,
	BACK_SLASH,
	EQUAL,
	DOT,
	D_DOT,
	ASTERISK,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	EXIT_STATUS,
	//LPAREN,
	//RPAREN,
	//COMMA,
	//INT,
	NON,
};
typedef enum e_token_type token_type;

typedef struct s_token
{
	token_type	type;
	char		*literal;
	size_t		len;
}	t_token;

t_token	*lexer(char *str);
#endif
