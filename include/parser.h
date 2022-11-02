/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:42:36 by hsano             #+#    #+#             */
/*   Updated: 2022/11/02 11:13:16 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CMD_H
# define CMD_H
# include "lexer.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

enum e_fd
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
};
typedef enum e_fd t_fd;

typedef struct s_pipe {
	char	*in_file;
	char	*out_file;
	int	write_option;
	char	*cmd;
	int	have_param;
	char	**param;
	size_t	id;
	size_t	cmd_num;
	int	is_builtin_cmd;
}	t_pipe;

typedef struct s_pipes {
	t_pipe	*pipe;
	size_t	len;
}	t_pipes;

typedef struct s_cmds {
	int		result;
	size_t		id;
	//size_t		pipe_len;
	t_pipe		*pipes;
	size_t		len;
	token_type	operator;
	int		last;
}	t_cmds;

t_cmds	*parser(t_token *tokens);
#endif
