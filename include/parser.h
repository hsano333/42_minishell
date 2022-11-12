/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:42:36 by hsano             #+#    #+#             */
/*   Updated: 2022/11/13 03:14:00 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
//# include "lexer_util.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

typedef enum e_fd
{
	STD_IN = 0,
	STD_OUT,
	STD_OUT_APPEND,
	SAVED_FILE,
	SAVED_FILE_APPEND,
	NONEXISTENT_FILE,
	HERE_DOC,
	STD_ERR,
	FD_PIPE,
	ERROR,
}	t_fd;

typedef struct s_pipe {
	char	*in_file;
	char	*out_file;
	int		write_option;
	int		option_fd_in;
	int		option_fd_out;
	char	*cmd;
	int		have_param;
	char	**param;
	size_t	id;
	size_t	param_num;
	int		is_builtin_cmd;
}	t_pipe;

typedef struct s_pipes {
	t_pipe	*pipe;
	size_t	len;
}	t_pipes;

typedef struct s_cmds {
	int				result;
	size_t			id;
	t_pipe			*pipes;
	size_t			len;
	int				last;
	t_token_type	operator;
}	t_cmds;

t_cmds	*parser(t_token *tokens);
#endif
