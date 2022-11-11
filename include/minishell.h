/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:42:18 by hsano             #+#    #+#             */
/*   Updated: 2022/11/11 12:23:54 by hsano            ###   ########.fr       */
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

// signal
void	handle_global_signals(void);
void	handle_cmd_signals(void);
void	handle_heredoc_signals(void);

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
void	update_pwd(char **cwd);
void	check_pwd(char **cwd);
int		exit_cd(char **cwd, int exit_status, char *dname);
int		cmd_exit(char **cmd);
int		is_builtin(char **cmd);
bool	has_option(char **cmd);

#endif
