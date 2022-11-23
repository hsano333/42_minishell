/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:52:28 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/23 18:37:31 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

static int	unset_error_loop(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] != '\0')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	cmd_unset(char **cmd)
{
	size_t	i;

	i = 1;
	if (!cmd[i])
		return (EXIT_FAILURE);
	while (cmd[i])
	{
		if (unset_error_loop(cmd[i]) == EXIT_FAILURE)
		{
			i++;
			exit_status = EXIT_FAILURE;
			continue ;
		}
		del_env_var(cmd[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
