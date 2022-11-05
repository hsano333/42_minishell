/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:41:45 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/05 19:21:31 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "exit_status.h"

static bool	is_sign(char c)
{
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

static bool	is_valid_exit_arg(char *args[])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args && args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (is_sign(args[i][j]))
				j++;
			if (!ft_isdigit(args[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	cmd_exit(char **cmd)
{
	long	exit_code;
	int		check_overflow;
	size_t	i;

	i = 1;
	check_overflow = true;
	if (cmd[i])
		exit_code = ft_atol(cmd[i], &check_overflow);
	else
		exit_code = get_exit_status();
	if (!is_valid_exit_arg(cmd + i))
	{
		ft_putstr_fd("exit: not a valid argument\n", 2);
		exit_code = 255;
	}
	else if (cmd[i] && cmd[++i])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd("exit\n", 2);
	exit(exit_code);
	return (exit_code);
}
