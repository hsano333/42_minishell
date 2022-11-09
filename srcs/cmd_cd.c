/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:50:43 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/05 19:15:46 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

static char	*find_home(void)
{
	char	*path;

	path = get_env_val("HOME");
	if (ft_strlen(path) == 0)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		free(path);
	}
	return (path);
}

int	exit_cd(char **cwd, int exit_status, char *dname)
{
	char	*err_msg;

	free(*cwd);
	if (exit_status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (exit_status == EXIT_FAILURE && dname)
	{
		err_msg = ft_strjoin("cd: ", dname);
		perror(err_msg);
		free(err_msg);
		return (EXIT_FAILURE);
	}
	else
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
}

static int	cd_home(void)
{
	char	*home_path;
	char	*cwd;

	cwd = NULL;
	home_path = find_home();
	if (!home_path)
		return (EXIT_FAILURE);
	if (chdir(home_path) != 0)
	{
		free(home_path);
		return (exit_cd(&cwd, EXIT_FAILURE, NULL));
	}
	update_pwd(&cwd);
	free(home_path);
	check_pwd(&cwd);
	return (exit_cd(&cwd, EXIT_SUCCESS, NULL));
}

int	cmd_cd(char **cmd)
{
	char	*cwd;
	DIR		*directory;

	if (!cmd)
		return (EXIT_FAILURE);
	if (!cmd[1])
		return (cd_home());
	cwd = NULL;
	directory = opendir(cmd[1]);
	if (!directory)
		return (exit_cd(&cwd, EXIT_FAILURE, cmd[1]));
	else if (closedir(directory) != 0)
		return (exit_cd(&cwd, EXIT_FAILURE, NULL));
	else if (chdir(cmd[1]) != 0)
		return (exit_cd(&cwd, EXIT_FAILURE, NULL));
	update_pwd(&cwd);
    check_pwd(&cwd);
	return (exit_cd(&cwd, EXIT_SUCCESS, NULL));
}
