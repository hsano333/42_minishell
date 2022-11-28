/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:50:43 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/28 22:18:00 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

char	*pathjoin(char *prev, char *next)
{
	char	*joined;
	char	*tmp;

	joined = ft_strjoin(prev, "/");
	if (!joined)
		return (NULL);
	tmp = ft_strdup(joined);
	if (!tmp)
		return (NULL);
	free(joined);
	joined = ft_strjoin(tmp, next);
	if (!joined)
		return (NULL);
	free(tmp);
	return (joined);
}

char	*build_symbolic_path(char **split, char *lastpath)
{
	char	*joined;
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = ft_strdup("");
	while (split[i + 1])
	{
		joined = pathjoin(tmp, split[i]);
		if (!joined)
			return (NULL);
		free(tmp);
		tmp = ft_strdup(joined);
		free(joined);
		i++;
	}
	joined = pathjoin(tmp, lastpath);
	if (!joined)
		return (NULL);
	free(tmp);
	return (joined);
}

void	update_pwd_with_synbl(char **cwd, char *lastpath)
{
	char	**split;
	char	*joined;

	split = ft_split(*cwd, '/');
	if (ft_strrchr(lastpath, '/'))
		lastpath = ft_strrchr(lastpath, '/') + 1;
	joined = build_symbolic_path(split, lastpath);
	printf("synbl: %s\n", joined);
	update_pwd(&joined);
	free(joined);
	free_str_array(&split);
}

void	update_pwd(char **cwd)
{
	char	*old_pwd;
	char	*pwd;
	char	*tmp_pwd;

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

void	check_pwd(char **cwd)
{
	char	*pwd;
	char	*old_pwd;

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
