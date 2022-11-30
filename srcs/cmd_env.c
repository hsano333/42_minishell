/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:33:39 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/30 19:06:52 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	_print_env(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strchr(env[i], '='))
		{
			i++;
			continue ;
		}
		if (printf("%s\n", env[i++]) == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	cmd_env(char **cmd)
{
	char	**env;

	env = env_store(NULL, GET_ENV);
	if (!env)
		return (EXIT_FAILURE);
	if (cmd && cmd[1])
	{
		if (access(cmd[1], F_OK) == 0)
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (126);
		}
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file ir directory\n", 2);
		return (127);
	}
	return (_print_env(env));
}
