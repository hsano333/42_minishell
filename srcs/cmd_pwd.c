/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:46:10 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/28 21:47:17 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	cmd_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = get_env_val("PWD");
	if (!cwd)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
	else if (printf("%s\n", cwd) != (int)ft_strlen(cwd) + 1)
	{
		free(cwd);
		perror("\nError: printf failed");
		return (EXIT_FAILURE);
	}
	free(cwd);
	return (EXIT_SUCCESS);
}
