/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:28:23 by hsano             #+#    #+#             */
/*   Updated: 2022/10/28 20:52:51 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_util.h"

void	write_file(int fd_in, char *filename)
{
	int		fd_out;
	int		read_size;
	//int		option;
	char	buf[READ_MAX];

	//return ;
	//option = O_WRONLY | O_CREAT | O_TRUNC;
	//return ;
	if (filename)
		fd_out = open(filename, O_WRONLY);
	else
		fd_out = 1;
	if (fd_out < 0)
		kill_process(-1, filename, NULL);
	while (1)
	{
		read_size = read(fd_in, buf, READ_MAX);
		if (read_size > 0)
			write(fd_out, buf, read_size);
		else
			break ;
	}
	close(fd_out);
}
