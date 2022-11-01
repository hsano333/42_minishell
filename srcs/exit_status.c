/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:37:16 by hsano             #+#    #+#             */
/*   Updated: 2022/10/26 16:22:08 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "libft_str.h"

static int	saved_exit_status(int e_stat)
{
	static int	exit_status = 0;

	if (e_stat >= 0)
		exit_status = e_stat;
	return (exit_status);
}

void	set_exit_status(int e_stat)
{
	saved_exit_status(e_stat);
}

int	get_exit_status(void)
{
	return (saved_exit_status(-1));
}

void	get_exit_status_str(char *e_status)
{
	char	p[20];

	ft_itoa_no_memory(saved_exit_status(-1), &(p[0]), &(e_status[0]));
}
