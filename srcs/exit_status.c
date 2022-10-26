/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:37:16 by hsano             #+#    #+#             */
/*   Updated: 2022/10/25 23:57:41 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
