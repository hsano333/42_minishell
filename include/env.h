/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:13:58 by hsano             #+#    #+#             */
/*   Updated: 2022/10/26 14:07:44 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

#include <stdbool.h>
#include <stdio.h>
#include <minishell.h>

enum e_env_mode
{
	INIT_ENV,
	GET_ENV,
	GET_ENV_VAR,
	SET_ENV_VAR,
	DEL_ENV_VAR,
};

typedef enum e_env_mode t_env_mode;

char **env_func(char ***src_env, t_env_mode mode, char *var, char *val);

#endif
