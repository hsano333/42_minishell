/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:27:26 by hsano             #+#    #+#             */
/*   Updated: 2022/11/04 05:14:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIR_H
# define DIR_H

typedef enum e_dir_mode
{
	GET_DIR,
	SET_DIR,
}	t_dir_mode;

char	*get_cur_dir(void);
void	set_cur_dir(char *dir);
#endif
