/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_delete_ast.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:55:33 by hsano             #+#    #+#             */
/*   Updated: 2022/11/29 15:44:35 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_expand.h"
//#include "parser_find_cmds_util.h"
#include "libft_str.h"
//#include "env.h"

int	delete_consecutive_ast(char *str, char **bk)
{
	size_t	i;
	size_t	len;

	i = 0;
	*bk = ft_strdup(str);
	if (!*bk)
		return (false);
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '*' && str[i + 1] == '*')
		{
			ft_memmove(&(str[i]), &(str[i + 1]), len - i);
			i--;
		}
		i++;
	}
	if (strncmp(str, *bk, ft_strlen(str) + 1) == 0)
	{
		free(*bk);
		*bk = NULL;
	}
	return (true);
}

int	free_ast_bk(char *bk)
{
	free(bk);
	bk = NULL;
	return (true);
}
