/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:28:23 by hsano             #+#    #+#             */
/*   Updated: 2022/11/06 19:42:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_util.h"

void	write_file(int fd_in, char *filename)
{
	int		fd_out;
	int		read_size;
	char	buf[READ_MAX];

	return ;
	printf("write fd_in=%d\n", fd_in);
	if (filename)
		fd_out = open(filename, O_WRONLY);
	else
		fd_out = 1;
	if (fd_out < 0)
		kill_process(-1, filename, NULL);
	while (1)
	{
		printf("write read test No.1\n");
		read_size = read(fd_in, buf, READ_MAX);
		printf("write read test No.2, read_size=%d\n", read_size);
		if (read_size > 0)
			write(fd_out, buf, read_size);
		else
			break ;
	}
	close(fd_out);
}
