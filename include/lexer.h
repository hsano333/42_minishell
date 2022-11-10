/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:56:01 by hsano             #+#    #+#             */
/*   Updated: 2022/11/10 13:03:12 by hsano            ###   ########.fr       */
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

typedef enum e_token_type
{
	NON = 0,
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
	WHITE_SPACE,
	DOLLER = 256,
	ASTERISK = 512,
	EXIT_STATUS = 1024,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	int				option_fd;
	char			*literal;
	size_t			len;
	size_t			id;
	int				valid;
	int				expand;
	int				error;
	int				concat;
}	t_token;

t_token	*lexer(char *str);
size_t	expand_str(t_token *tokens, t_token_type pre_token, size_t i);
#endif
