/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:47:45 by hsano             #+#    #+#             */
/*   Updated: 2022/10/13 03:42:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_val(char *var)
{
	if (!var)
		return ft_strdup("");
	return (ft_strdup("hsano"));
}

int	*set_env(char *var, char *val)
{

	(void )var;
	(void )val;
	return (0);
}
