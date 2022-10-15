
#ifndef CMD_H
# define CMD_H

#include "lexer.h"
#include "stdlib.h"

enum e_fd
{
	STD_IN = 0,
	STD_OUT,
	STD_ERR,
	FD_PIPE,
};
typedef enum e_fd t_fd;
typedef struct s_cmd {
	t_fd	in;
	char	**cmd;
	t_fd	out;
	size_t	no;
}	t_cmd;

#endif
