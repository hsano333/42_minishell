/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstr_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:14:38 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/12 10:45:56 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_isto.h"
#include <stdbool.h>
#include <stdio.h>

bool	ft_is_str_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}
