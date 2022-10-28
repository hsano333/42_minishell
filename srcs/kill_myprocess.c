/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_myprocess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:41:04 by hsano             #+#    #+#             */
/*   Updated: 2022/10/28 16:01:34 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kill_myprocess.h"

void	kill_myprocess(int no, char *message1, t_token *tokens, t_cmds *cmds)
{
	printf("kill myprocess No.1\n");
	clear_tokens(tokens);
	clear_all_cmds(&cmds);
	if (no == 0)
	{
		if (message1)
			printf("Error:%s\n", message1);
		exit(EXIT_FAILURE);
	}
	else if (no == -1)
	{
		no = errno;
		if (message1)
			perror(message1);
		else
			strerror(no);
		exit(no);
	}
	errno = no;
	if (message1)
		printf("\n%s:%s\n", strerror(errno), message1);
	else
		strerror(no);
	exit(no);
}
