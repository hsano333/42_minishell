/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:39:31 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/30 01:57:40 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include <fcntl.h>
#include "parser.h"

static int	change_buildin_fd_inout(int fd_inout \
		, char *filename, int option, int *fd)
{
	*fd = fd_inout;
	if (filename)
	{
		close(*fd);
		*fd = open(filename, option);
		if (*fd < 0)
		{
			ft_putstr_fd("open error:", 2);
			write(2, filename, ft_strlen(filename));
			write(2, "\n", 1);
			return (false);
		}
	}
	if (dup2(*fd, fd_inout) == -1)
		return (false);
	return (true);
}

static int	change_buildin_fd(t_pipe *pipe, int back)
{
	static int	pre_fd_in = 0;
	static int	pre_fd_out = 1;
	static int	fd_in = 0;
	static int	fd_out = 1;

	if (back == false)
	{
		pre_fd_in = dup(pipe->option_fd_in);
		pre_fd_out = dup(pipe->option_fd_out);
		change_buildin_fd_inout(pipe->option_fd_in \
		, pipe->in_file, O_RDONLY, &fd_in);
		change_buildin_fd_inout(pipe->option_fd_out \
		, pipe->out_file, O_APPEND | O_WRONLY, &fd_out);
	}
	else if (back == true)
	{
		if (fd_out != 1)
			close(fd_out);
		if (fd_in != 1)
			close(fd_in);
		dup2(pre_fd_in, 0);
		dup2(pre_fd_out, 1);
	}
	return (true);
}

int	exec_builtin_cmd(char **cmd)
{
	if (!cmd || !cmd[0])
		return (EXIT_FAILURE);
	if (ft_strncmp(cmd[0], "echo", ft_strlen("echo")) == 0)
		return (cmd_echo(cmd));
	if (ft_strncmp(cmd[0], "exit", ft_strlen("exit")) == 0)
		return (cmd_exit(cmd));
	if (has_option(cmd))
		return (EXIT_FAILURE);
	if (ft_strncmp(cmd[0], "cd", ft_strlen("cd")) == 0)
		return (cmd_cd(cmd));
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

int	builtin_wrapper(char **cmd, t_pipe *pipe_info)
{
	int	rval;

	change_buildin_fd(pipe_info, false);
	rval = exec_builtin_cmd(cmd);
	change_buildin_fd(pipe_info, true);
	return (rval);
}

int	is_builtin(char **cmd)
{
	const char	*commands[] = {
		"exit", "cd", "echo", "pwd", "env", "export", "unset", NULL};
	int			i;

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
