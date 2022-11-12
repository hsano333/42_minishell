/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:52:28 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/13 08:51:46 by maoyagi          ###   ########.fr       */
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
		del_env_var(cmd[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
