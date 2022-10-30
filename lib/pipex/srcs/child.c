/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:58:19 by hsano             #+#    #+#             */
/*   Updated: 2022/10/31 00:59:25 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "child.h"

static void	put_invalid_command(char *cmds)
{
	write(2, "zsh: command not found: ", 25);
	write(2, cmds, ft_strlen(cmds));
	write(2, "\n", 1);
	exit(0);
}

void	child(int fd_in, int *pipe_fd, t_pipe *pipes, char **environ, int is_last)
{
	char		filepath[PATH_MAX + 1];
	int			r[2];

	if (pipes->param)
	{
		if (search_path(pipes->param[0], environ, filepath))
		{
			close(pipe_fd[PIPE_IN]);
			if (pipes->in_file)
			{
				close(fd_in);
				fd_in = open(pipes->in_file, O_RDONLY);;
			}
			r[0] = dup2(fd_in, 0);
			r[1] = 1;
			if (!is_last || (is_last && pipes->out_file))
				r[1] = dup2(pipe_fd[PIPE_OUT], 1);
			if (r[0] == -1 || r[1] == -1)
				exit(EXIT_FAILURE);
			printf("execve No.1\n");
			if (execve(filepath, pipes->param, environ) == -1)
				exit(EXIT_FAILURE);
			printf("execve No.2\n");
		}
		else
			put_invalid_command(pipes->param[0]);
		printf("execve No.3\n");
	}
}
