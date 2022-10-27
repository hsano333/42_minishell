/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:30:56 by hsano             #+#    #+#             */
/*   Updated: 2022/10/26 16:04:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H
# include "libft_str.h"
void	set_exit_status(int e_stat);
int	get_exit_status(void);
void	get_exit_status_str(char *e_status);
#endif
