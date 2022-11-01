/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_option_validate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 07:26:08 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/02 00:39:52 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

bool has_option(char **cmd)
{
    size_t i;

    i = 0;
    while (cmd[i])
    {
        if (i == 1 && cmd[i][0] == '-')
        {
            ft_putstr_fd("has no option!!\n", 2);
            return (true);
        }
        i++;
    }
    return (false);
}
