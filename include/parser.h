/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:42:36 by hsano             #+#    #+#             */
/*   Updated: 2022/11/18 15:11:53 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
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
	int		heredoc_fd;
	char	*cmd;
	int		have_param;
	char	**param;
	size_t	id;
	size_t	param_num;
	int		is_builtin_cmd;
	int		is_subshell;
	t_token	*sub_tokens;
	size_t	sub_tokens_size;
	int		subshell_error;
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
	int				has_subshell;
	t_token_type	operator;
}	t_cmds;

t_cmds	*parser(t_token *tokens);
#endif
