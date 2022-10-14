/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/10/14 02:54:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"
#include "lexer.h"
#include "lexer_util.h"
#include "env.h"

//簡易的な入力受付
int loop(t_env *env)
{
	char	*line;
	int		exit_code;
	t_token	*tokens;

	(void)env;

	exit_code = 0;
	while (true)
	{
		line = readline("\033[31mminishell$ \033[0m");
		if (!line || ft_strlen(line) == 0)
		{
			printf("exit\n");
			free(line);
			break;
		}



		tokens = lexer(line);
		put_tokens(tokens);
		expand_str(tokens, NON, 0);
		printf("\n");
		put_tokens(tokens);
		// lexer parser

		printf("%s\n", line);
		add_history(line);
		free(line);
	}
	return (exit_code);
}

/*
int main(int argc, char **argv, char **envp)
{
	t_env *env;

	(void)argc;
	(void)argv;

	env = init_env(envp);

	print_env(env);

	// readline
	loop(env);

	free_env(env);

	return (0);
}
*/

int main(int argc, char **argv, char **envp)
{
	t_env *env;

	(void)argc;
	(void)argv;

	env = init_env(envp);

	print_env(env);
	env_func(envp, 0, NULL, NULL);
	printf("env test:%s\n", env_func(NULL, 1, NULL, NULL));

	// readline
	loop(env);

	free_env(env);

	return (0);
}
