/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:55:37 by hsano             #+#    #+#             */
/*   Updated: 2022/11/01 12:15:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARENT_H
# define PARENT_H
# include "pipex.h"
# include "pipex_util.h"
# include "libft_str.h"
# include "ft_printf.h"

t_fdpid	parent(int pid, int *pipe_fd, t_pipe *pipes, int is_last);
#endif
