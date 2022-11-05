/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:52:28 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/05 19:40:50 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	cmd_unset(char **cmd)
{
	size_t	i;

	i = 1;
	if (!cmd[i])
		return (EXIT_FAILURE);
	while (cmd[i])
	{
		if (del_env_var(cmd[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
