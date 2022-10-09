/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:28:22 by maoyagi           #+#    #+#             */
/*   Updated: 2022/10/09 23:28:22 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//

t_env *init_env(char **envp)
{
    t_env *env;

    env = ft_calloc(1, sizeof(t_env));
    //アドレスがなくて、実体が無い場合も。要素が無い場合は不要なので
    if (env && envp && (*envp))
    {
        env->env_var = str_arr_dup(envp);
    }
    //のちのち他の変数もチェックするようにする
    if (env->env_var)
        return (env);
    else
        return (NULL);
}

void free_env(t_env *env)
{
    free_str_array(&env->env_var);

    // free(env->env_var);
    free(env);
    env = NULL;
}

//簡単に出力してみる
void print_env(const t_env *env)
{
    for (size_t i = 0; env->env_var[i] != NULL; i++)
    {
        printf("%zu: [%s]\n", i, env->env_var[i]);
    }
}