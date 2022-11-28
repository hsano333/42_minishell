/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:15:59 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/28 22:47:13 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

static int	export_exit(char ***env, bool exit_status)
{
	free_str_array(env);
	return (exit_status);
}

static int	sort_env(char **env, size_t i, size_t j)
{
	char	*tmp;

	tmp = NULL;
	while (env[i] && env[i + 1])
	{
		j = i + 1;
		while (env[j])
		{
			if ((ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0) \
				|| (ft_strncmp(env[i], env[j], ft_strlen(env[j])) > 0))
			{
				tmp = ft_strdup(env[i]);
				if (!tmp)
					return (EXIT_FAILURE);
				free(env[i]);
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	_print_env_export_line(char *line)
{
	size_t	i;
	bool	quote_flag;

	quote_flag = false;
	i = 0;
	printf("declare -x ");
	while (line[i])
	{
		if (&line[i] == ft_strchr(line, '='))
		{
			quote_flag = true;
			printf("%c\"", line[i++]);
		}
		else
			printf("%c", line[i++]);
	}
	if (quote_flag)
		printf("\"");
	printf("\n");
	return (EXIT_SUCCESS);
}

int	_print_env_export(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "_=", 2))
		{
			i++;
			continue ;
		}
		_print_env_export_line(env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	export_only(const char **env)
{
	char	**env_cpy;
	size_t	i;
	size_t	j;

	env_cpy = str_arr_dup((char **)env);
	if (!env_cpy)
		return (EXIT_FAILURE);
	i = 0;
	j = 0;
	if (sort_env(env_cpy, i, j) == EXIT_FAILURE)
		return (export_exit(&env_cpy, EXIT_FAILURE));
	_print_env_export(env_cpy);
	return (export_exit(&env_cpy, EXIT_SUCCESS));
}
