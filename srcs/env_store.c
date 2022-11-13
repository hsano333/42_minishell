/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 08:34:37 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/13 11:25:44 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"
#include "env.h"
#include <minishell.h>

char	**get_env(void)
{
	char	**env;

	env = env_store(NULL, GET_ENV);
	return (env);
}

void	initialize_env(char **envp)
{
	env_store(envp, INIT_ENV);
}

char	**env_store(char **envp, t_env_mode mode)
{
	static char	**env = NULL;

	if (mode == GET_ENV)
		return (env);
	else if (mode == INIT_ENV)
		env = envp;
	return (NULL);
}
