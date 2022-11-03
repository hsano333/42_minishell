/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:42:18 by hsano             #+#    #+#             */
/*   Updated: 2022/11/04 04:46:14 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>
# include "libft_str.h"
# include "libft_mem.h"
# include "libft_put.h"
# include "libft_isto.h"
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

int	g_pid;
typedef struct sigaction	t_sigactio;
typedef struct s_env
{
	char		**env_var;
	char		*pwd;
	char		*oldpwd;
	t_sigaction	act;
}	t_env;

typedef enum e_signal_mode
{
	DEFAULT_MODE,
	FORK_MODE,
	CHILD_MODE,
}t_signal_mode;

// env
t_env	*init_env(char **envp);
void	free_env(t_env *env);
void	print_env(const t_env *env);
void	print_env2(const char **env);

// signal
bool	init_signal(t_sigaction *act);
bool	set_signal(t_signal_mode mode);
void	handle_global_signals(void);
void	handle_cmd_signals(void);

// utils
int		str_arr_len(char **arr);
char	**str_arr_dup(char **arr);
void	free_str_array(char ***arr);
char	**realloc_str_arr(char **arr, size_t size);

// cmd
int		exec_builtin_cmd(char **cmd);
int		cmd_env(char **cmd);
int		cmd_pwd(void);
int		cmd_echo(char **cmd);
int		export_only(const char **env);
int		cmd_export(char **cmd);
int		cmd_unset(char **cmd);
int		cmd_cd(char **cmd);
int		cmd_exit(char **cmd);
int		is_builtin(char **cmd);
bool	has_option(char **cmd);

#endif
