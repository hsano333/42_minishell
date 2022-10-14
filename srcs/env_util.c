/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:47:45 by hsano             #+#    #+#             */
/*   Updated: 2022/10/14 02:53:29 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"
#include "env.h"

static char	*get_env_val(char **env, char *var)
{
	if (env)
		if (!var)
			return ft_strdup(env[3]);
	return (ft_strdup(env[5]));
}

static int	set_env(char **env, char *var, char *val)
{

	(void )var;
	(void )val;
	//(void )env;
	if (env == NULL)
		return (1);
	return (0);
}

char	*env_func(char **envp, t_env_mode mode, char *var, char *val)
{
	static char **env = NULL;

	if (mode == INIT_ENV)
		env = envp;
	else if (mode == GET_ENV)
		return get_env_val(env, var);
	else if (mode == SET_ENV)
		set_env(env, var, val);
	return (NULL);
}
