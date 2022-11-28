/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:50:43 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/28 22:23:46 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static char	*find_home(void)
{
	char	*path;

	path = get_env_val("HOME");
	if (ft_strlen(path) == 0)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		free(path);
		return (NULL);
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
	char		*cwd;
	struct stat	buf;
	int			ret;
	bool		is_synbl;

	is_synbl = false;
	if (!cmd)
		return (EXIT_FAILURE);
	if (!cmd[1])
		return (cd_home());
	cwd = NULL;
	ret = lstat(cmd[1], &buf);
	if (ret < 0)
		return (EXIT_FAILURE);
	if ((S_ISLNK(buf.st_mode)))
		is_synbl = true;
	if (chdir(cmd[1]) != 0)
		return (exit_cd(&cwd, EXIT_FAILURE, NULL));
	cwd = getcwd(cwd, 0);
	if (is_synbl)
		update_pwd_with_synbl(&cwd, cmd[1]);
	else
		update_pwd(&cwd);
	check_pwd(&cwd);
	return (exit_cd(&cwd, EXIT_SUCCESS, NULL));
}
