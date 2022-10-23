/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:56:01 by hsano             #+#    #+#             */
/*   Updated: 2022/10/24 01:31:35 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <unistd.h>

enum	e_buildin
{
	BUIDIN_ECHO,
	BUIDIN_CD,
	BUIDIN_PWD,
	BUIDIN_EXPORT,
	BUIDIN_UNSET,
	BUIDIN_ENV,
	BUIDIN_EXIT,
	NOT_BUIDIN,
};

enum	e_token_type
{
	IDENT = 1,
	ILLEGAL,
	EOS,
	IDENT_DOLLER,
	IDENT_ASTERISK,
	IDENT_ASTERISK_DOLLER,
	PIPE,
	D_PIPE,
	D_AMPERSAND,
	GLT,
	GT,
	LT,
	D_GT,
	D_LT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	EXIT_STATUS,
	NON,
	DOLLER = 256,
	ASTERISK = 512,
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
};
typedef enum e_token_type token_type;

typedef struct s_token
{
	token_type	type;
	char		*literal;
	size_t		len;
	size_t		id;
	int		valid;
	int		error;
}	t_token;


t_token	*lexer(char *str);
size_t	expand_str(t_token *tokens, token_type pre_token, size_t i);
#endif
