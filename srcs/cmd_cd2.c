/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:50:43 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/05 19:15:46 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

void    update_pwd(char **cwd)
{
    char    *old_pwd;
    char    *pwd;
    char    *tmp_pwd;

    tmp_pwd = get_env_val("PWD");
    old_pwd = ft_strjoin("OLDPWD=", tmp_pwd);
    *cwd = getcwd(*cwd, 0);
    pwd = ft_strjoin("PWD=", *cwd);
    set_env_var(old_pwd);
    set_env_var(pwd);
    free(old_pwd);
    free(pwd);
    free(tmp_pwd);
}

void    check_pwd(char **cwd)
{
    char    *pwd;
    char    *old_pwd;

    pwd = get_env_val("PWD");
    old_pwd = get_env_val("OLDPWD");
    if (!old_pwd || !pwd)
    {
        free(old_pwd);
        free(pwd);
        exit_cd(cwd, EXIT_FAILURE, NULL);
    }
    free(old_pwd);
    free(pwd);
}
