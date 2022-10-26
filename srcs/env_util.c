/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:47:45 by hsano             #+#    #+#             */
/*   Updated: 2022/10/26 16:00:02 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"
#include "env.h"
#include <minishell.h>

static char *get_env_val(char **env, char *var)
{
	size_t i;
	char *value;

	i = 0;
	value = NULL;
	//環境変数の最後まで読む
	while (env && var && env[i])
	{
		//差分が=の時。つまり存在した時
		if (ft_strncmp(env[i], var, ft_strlen(env[i])) == '=')
		{
			value = ft_strchr(env[i], '=') + 1;
			//値がない場合
			if (!value)
				value = ft_calloc(1, sizeof(char));
			else
				value = ft_strdup(value);
			break;
		}
		//=も無かった時
		//行数制限回避の為、breakだけにする
		else if (ft_strncmp(env[i], var, ft_strlen(env[i])) == '\0')
		{
			value = ft_calloc(1, sizeof(char));
			break;
		}
		i++;
	}
	if (!value)
		value = ft_calloc(1, sizeof(char));
	return (value);
}

bool del_env_var(char **env, char *var)
{
	size_t i;

	i = 0;
	if (!var)
		return (false);
	while (env && env[i] && ft_strncmp(env[i], var, ft_strlen(env[i]) != '='))
		i++;
	free(env[i]);
	env[i] = NULL;
	//一個ずらす
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
		if (env[i + 1] == NULL)
			env[i] = NULL;
	}
	return (true);
}

//トリプルポインタにしないと、envのアドレスがnewに置き変わらない
//ダブルポインタのメモリ確保を関数内で行うにはアドレスを渡す必要があるらしい
bool set_env_var(char ***env, char *var)
{
	size_t i;
	char **new;

	i = 0;
	if (!(*env) || !var)
		return (false);
	//変更

	while ((*env) && (*env)[i] && ft_strncmp((*env)[i], var, ft_strlen((*env)[i])) != '=')
		i++;
	/*
if (i < (size_t)str_arr_len(*env))
{
	free((*env)[i]);
	(*env)[i] = ft_strdup(var);
	if (!(*env)[i])
		return (false);
}
*/
	// else
	//{
	new = realloc_str_arr(*env, str_arr_len(*env) + 1);
	if (!new)
		return (false);
	new[str_arr_len(new)] = ft_strdup(var);
	if (!new[str_arr_len(new) - 1])
		return (false);
	*env = new;
	//}
	return (true);
}

// char *strに変更
char **env_func(char ***envp, t_env_mode mode, char *var, char *val)
{
	static char ***env = NULL;
	char **value;

	(void)val;
	value = NULL;
	if (mode == INIT_ENV)
		env = envp;
	else if (mode == GET_ENV)
		return *env;
	else if (mode == GET_ENV_VAR)
	{
		*value = get_env_val(*env, var);
		return (value);
	}
	else if (mode == SET_ENV_VAR)
		set_env_var(env, var);
	else if (mode == DEL_ENV_VAR)
		del_env_var(*env, var);
	return (NULL);
}
