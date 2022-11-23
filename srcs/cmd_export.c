/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:53:43 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/23 19:13:25 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

static int	export_error_loop(char **var, char *cmd)
{
	size_t	i;

	i = 0;
	while ((*var)[i] != '\0')
	{
		if (cmd[0] == '=' || (ft_isalnum((*var)[i]) == 0 && (*var)[i] != '_'))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	export_input_error(char *cmd)
{
	char	**split;
	char	*var;

	var = NULL;
	split = ft_split(cmd[i], '=');
	if (!split)
		return (EXIT_FAILURE);
	var = ft_strdup(split[0]);
	if (!var)
		return (EXIT_FAILURE);
	if (export_error_loop(&var, cmd[i]) == EXIT_FAILURE)
	{
		free(var);
		free_str_array(&split);
		return (EXIT_FAILURE);
	}
	free(var);
	free_str_array(&split);
	return (EXIT_SUCCESS);
}

void	export_with_argments(size_t *i, char **cmd, int *exit_status)
{
	*i = 1;
	while (cmd[*i])
	{
		if (export_input_error(cmd[*i]) == EXIT_FAILURE)
		{
			(*i)++;
			*exit_status = EXIT_FAILURE;
			continue ;
		}
		if (!set_env_var(cmd[*i]))
		{
			*exit_status = EXIT_FAILURE;
			return ;
		}
		(*i)++;
	}
}

int	cmd_export(char **cmd)
{
	size_t	i;
	char	**env;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	env = env_store(NULL, GET_ENV);
	if (!env)
		return (EXIT_FAILURE);
	if (cmd && !cmd[1])
		export_only((const char **)env);
	else
		export_with_argments(&i, cmd, &exit_status);
	return (exit_status);
}
