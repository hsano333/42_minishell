/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:33:34 by maoyagi           #+#    #+#             */
/*   Updated: 2022/10/26 08:33:34 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_echo(char **cmd)
{
    bool print_newline;
    size_t i;

    print_newline = true;
    i = 1;
    if (cmd[i] && ft_strncmp(cmd[i], "-n", ft_strlen("-n")) == 0)
    {
        print_newline = false;
        i++;
    }
    while (cmd[i])
    {
        if (printf("%s", cmd[i]) != (int)ft_strlen(cmd[i]))
            return (EXIT_FAILURE);
        if (ft_strlen(cmd[i]) != 0 && cmd[i + 1])
            printf(" ");
        i++;
    }
    if (print_newline)
        printf("\n");
    return (EXIT_SUCCESS);
}