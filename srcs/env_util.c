/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:47:45 by hsano             #+#    #+#             */
/*   Updated: 2022/11/05 20:01:04 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"
#include "env.h"
#include <minishell.h>

char	*get_env_val(char *var)
{
	size_t	i;
	char	*value;
	char	**env;

	env = env_store(NULL, GET_ENV);
	i = 0;
	value = NULL;
	while (env && var && env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(env[i])) == '=')
		{
			value = ft_strchr(env[i], '=') + 1;
			if (!value)
				value = ft_calloc(1, sizeof(char));
			else
				value = ft_strdup(value);
			break ;
		}
		else if (ft_strncmp(env[i], var, ft_strlen(env[i])) == '\0')
			break ;
		i++;
	}
	if (!value)
		value = ft_calloc(1, sizeof(char));
	return (value);
}

bool	del_env_var(char *var)
{
	size_t	i;
	char	**env;

	env = env_store(NULL, GET_ENV);
	i = 0;
	if (!var)
		return (false);
	while (env && env[i] && ft_strncmp(env[i], var, ft_strlen(env[i])) != '=')
		i++;
	if (!env[i])
		return (false);
	free(env[i]);
	env[i] = NULL;
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
		if (env[i + 1] == NULL)
			env[i] = NULL;
	}
	return (true);
}

bool	add_env_var(char **env, char *var_val)
{
	char	**new;

	if (!env || !var_val)
		return (false);
	new = realloc_str_arr(env, str_arr_len(env) + 1);
	if (!new)
		return (false);
	new[str_arr_len(new)] = ft_strdup(var_val);
	if (!new[str_arr_len(new) - 1])
		return (false);
	env_store(new, INIT_ENV);
	return (true);
}

bool	update_env_var(char **env, char *var_val, size_t i)
{
	if (!env[i])
		return (false);
	free((env)[i]);
	(env)[i] = ft_strdup(var_val);
	if (!(env)[i])
		return (false);
	return (true);
}

bool	set_env_var(char *var_val)
{
	size_t	i;
	char	**env;
	char	**split;

	env = env_store(NULL, GET_ENV);
	if (!(env) || !var_val)
		return (false);
	i = 0;
	split = ft_split(var_val, '=');
	while ((env) && \
		(env)[i] && ft_strncmp((env)[i], split[0], ft_strlen(env[i])) != '=')
		i++;
    free_str_array(&split);
	free(split);
	if (i < (size_t)str_arr_len(env))
		return (update_env_var(env, var_val, i));
	else
		return (add_env_var(env, var_val));
	return (true);
}
