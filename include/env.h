/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:13:58 by hsano             #+#    #+#             */
/*   Updated: 2022/11/04 05:15:04 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include <stdbool.h>
# include <stdio.h>
# include <minishell.h>

typedef enum e_env_mode
{
	INIT_ENV,
	GET_ENV,
}	t_env_mode;

char	**env_store(char **src_env, t_env_mode mode);
void	initialize_env(char **envp);
char	**get_env(void);
bool	set_env_var(char *var_val);
bool	del_env_var(char *var);
char	*get_env_val(char *var);
#endif
