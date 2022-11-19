/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:42:22 by maoyagi           #+#    #+#             */
/*   Updated: 2022/11/19 13:24:54 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "libft_str.h"
#include "stdbool.h"

void	shlvl_warning(char **shlvl, size_t *shlvl_val)
{
	free(*shlvl);
	*shlvl = ft_itoa(*shlvl_val);
	ft_putstr_fd("bash: warning: shell level (", 2);
	ft_putstr_fd(*shlvl, 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
	*shlvl_val = 1;
}

void	calc_shlvl(char *shlvl)
{
	char	*shlvl_var;
	size_t	shlvl_val;
	int		overflow;

	shlvl_val = (size_t)ft_atol(shlvl, &overflow);
	shlvl_val++;
	if (1000 <= shlvl_val)
		shlvl_warning(&shlvl, &shlvl_val);
	else if (shlvl_val < 1)
		shlvl_val = 0;
	free(shlvl);
	shlvl = ft_itoa(shlvl_val);
	shlvl_var = ft_strjoin("SHLVL=", shlvl);
	set_env_var(shlvl_var);
	free(shlvl);
	free(shlvl_var);
}

bool	update_shlvl(void)
{
	char	*shlvl;

	shlvl = get_env_val("SHLVL");
	if (!shlvl)
	{
		shlvl = ft_strdup("SHLVL=1");
		if (!shlvl)
			return (false);
		set_env_var(shlvl);
		free(shlvl);
	}
	else
		calc_shlvl(shlvl);
	return (true);
}
