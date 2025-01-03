/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:59:33 by hsano             #+#    #+#             */
/*   Updated: 2022/11/06 20:54:47 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILD_H
# define CHILD_H
# include "pipex.h"
# include "pipex_util.h"
# include "libft_str.h"
# include "parser.h"

void	child(int fd_in, int *pipe_fd, t_pipe *pipes, char **environ);
#endif
