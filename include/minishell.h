/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:42:18 by hsano             #+#    #+#             */
/*   Updated: 2022/10/08 02:42:56 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_env
{
    char **env_var;
    char *pwd;
    char *oldpwd;
} t_env;

// env
t_env *init_env(char **envp);
void free_env(t_env *env);
void print_env(const t_env *env);

// utils
int str_arr_len(char **arr);
char **str_arr_dup(char **arr);
void free_str_array(char ***arr);

#endif
