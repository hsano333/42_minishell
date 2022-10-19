
#ifndef CMD_H
# define CMD_H
# include "lexer.h"
# include <stdlib.h>
# include <stdbool.h>


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
typedef struct s_cmd {
	t_fd	in;
	char	*in_file;
	char	*hiredoc_eos;
	char	**cmd;
	t_fd	out;
	char	*out_file;
	size_t	no;
	int		last;
}	t_cmd;

#endif
