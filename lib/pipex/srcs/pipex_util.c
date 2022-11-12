/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:11:07 by hsano             #+#    #+#             */
/*   Updated: 2022/11/12 16:42:01 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"
#include "libft_str.h"
#include "env.h"

void	kill_process(int no, char *message1, char *message2)
{
	dup2(2, 1);
	if (no == 0)
	{
		if (message1 || message2)
			ft_printf("Error:%s:%s\n", message1, message2);
		else if (message1)
			ft_printf("Error:%s\n", message1);
		exit(EXIT_FAILURE);
	}
	else if (no == -1)
	{
		perror(message1);
		exit(EXIT_FAILURE);
	}
	errno = no;
	if (message1)
		ft_printf("\n%s:%s\n", strerror(errno), message1);
	exit(EXIT_FAILURE);
}

static char	*concat_pathpath(char *filepath, char *env, char *exe)
{
	size_t	len;

	len = ft_strlen(env) + ft_strlen(exe) + 1 + 1;
	if (len > PATH_MAX + 1)
		kill_process(22, "Argument is too long\n", NULL);
	ft_strlcpy(filepath, env, ft_strlen(env) + 1);
	ft_strlcat(filepath, "/", ft_strlen(env) + 2);
	ft_strlcat(filepath, exe, len);
	return (filepath);
}

int	copy_filepath(char *dst, char *src)
{
	ft_strlcpy(dst, src, PATH_MAX + 1);
	return (true);
}

char	*search_path(char *exe, char *filepath)
{
	size_t	j;
	char	*paths;
	char	**tmp_paths;

	if ((exe && (exe[0] == '/' || exe[0] == '.')) \
			&& copy_filepath(filepath, exe))
		return (filepath);
	paths = get_env_val("PATH");
	tmp_paths = ft_split(paths, ':');
	j = 0;
	while (tmp_paths[j] && ft_strlen(tmp_paths[j]) + ft_strlen(exe) < PATH_MAX)
	{
		filepath = concat_pathpath(filepath, tmp_paths[j++], exe);
		if ((!access(filepath, X_OK)) && ft_free_split(tmp_paths))
		{
			free(paths);
			return (filepath);
		}
	}
	free(paths);
	ft_free_split(tmp_paths);
	return (NULL);
}
