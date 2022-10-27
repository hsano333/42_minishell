/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 08:34:37 by maoyagi           #+#    #+#             */
/*   Updated: 2022/10/27 08:34:37 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"
#include "env.h"
#include <minishell.h>

char **env_store(char **envp, t_env_mode mode)
{
    static char **env = NULL;

    if (mode == GET_ENV)
        return (env);
    else if (mode == INIT_ENV)
        env = envp;
    return (NULL);
}