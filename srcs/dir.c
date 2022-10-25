/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:27:03 by hsano             #+#    #+#             */
/*   Updated: 2022/10/15 16:55:53 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dir.h"
#include "unistd.h"

static char	*dir_func(char *src_dir, t_dir_mode mode)
{
	static char *curdir = NULL;

	if (mode == GET_DIR)
		return (curdir);
	else if (mode == SET_DIR)
		curdir = src_dir;
	return (NULL);
}

char	*get_cur_dir(void)
{
	return (dir_func(NULL, GET_DIR));
}
void	set_cur_dir(char *dir)
{
	dir_func(dir, SET_DIR);
}
