/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:39:31 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/02 11:29:57 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	exec_builtin_cmd(char **cmd)
{
    if (has_option(cmd))
        return (EXIT_FAILURE);
    if (ft_strncmp(cmd[0], "exit", ft_strlen("exit")) == 0)
        return (cmd_exit(cmd));
    if (ft_strncmp(cmd[0], "cd", ft_strlen("cd")) == 0)
        return (cmd_cd(cmd));
    if (ft_strncmp(cmd[0], "echo", ft_strlen("echo")) == 0)
        return (cmd_echo(cmd));
    if (ft_strncmp(cmd[0], "pwd", ft_strlen("pwd")) == 0)
        return (cmd_pwd());
    if (ft_strncmp(cmd[0], "env", ft_strlen("env")) == 0)
        return (cmd_env(cmd));
    if (ft_strncmp(cmd[0], "export", ft_strlen("export")) == 0)
        return (cmd_export(cmd));
    if (ft_strncmp(cmd[0], "unset", ft_strlen("unset")) == 0)
        return (cmd_unset(cmd));
    return (EXIT_FAILURE);
}

int	is_builtin(char **cmd)
{
    const char *commands[] = {
        "exit", "cd", "echo", "pwd", "env", "export", "unset", NULL};
    int i;

    i = 0;
    if (cmd[0] == NULL)
        return (0);
    while (commands[i])
    {
        if (ft_strncmp(cmd[0], (char *)commands[i], ft_strlen(cmd[0])) == 0)
            return (1);
        i++;
    }
    return (0);
}
