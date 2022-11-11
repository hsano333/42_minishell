/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:11:43 by hsano             #+#    #+#             */
/*   Updated: 2022/11/12 02:50:57 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include "parser.h"

typedef struct s_heredoc{
	int		valid;
	int		valid_backup;
	char	*limiter;
}	t_heredoc;

typedef struct s_fdpid{
	int		fd;
	int		pid;
	int		exe_pid;
}	t_fdpid;

int	pipex(t_cmds *cmds, char **environ);
#endif
