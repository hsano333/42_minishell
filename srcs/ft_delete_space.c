/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:00:47 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/29 23:10:41 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"
#include "env.h"
#include <minishell.h>

char	**delete_space(char **value)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(*value);
	i = 0;
	while ((*value)[i])
	{
		if ((*value)[i] == ' ' && (*value)[i + 1] == ' ')
		{
			ft_memmove(&((*value)[i]), &((*value)[i + 1]), len - i);
			i--;
		}
		i++;
	}
	return (value);
}
