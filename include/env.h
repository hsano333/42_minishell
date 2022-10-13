/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:13:58 by hsano             #+#    #+#             */
/*   Updated: 2022/10/14 02:54:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

enum e_env_mode
{
	INIT_ENV,
	GET_ENV,
	SET_ENV,
};

typedef enum e_env_mode t_env_mode;

char	*env_func(char **src_env, t_env_mode mode, char *var, char *val);
#endif
