/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/10/13 03:43:09 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"
#include "lexer.h"
#include "lexer_util.h"

//簡易的な入力受付
int loop(t_env *env)
{
	char *line;
	int exit_code;
	(void)env;

	exit_code = 0;
	while (true)
	{
		line = readline("\033[31mminishell$ \033[0m");
		if (!line || ft_strlen(line) == 0)
		{
			free(line);
			break;
		}

		// lexer parser

		printf("%s\n", line);
		add_history(line);
		free(line);
	}
	return (exit_code);
}

int main(int argc, char **argv, char **envp)
{
	t_env *env;

	(void)argc;
	(void)argv;

	env = init_env(envp);
	/*

	print_env(env);

	// readline
	loop(env);

	free_env(env);
	*/
	char *str = "$USER$PATH > test1 < $USE\'abcdef $USER\' \"abcd$USERtest\" $USER";

	//size_t	i;
	//i = 0;
	printf("%p:%p\n", envp,env);
	t_token *token = lexer(str);

	printf("test str:%s\n", str);
	put_tokens(token);
	expand_str(token, NON, 0);
	put_tokens(token);

	return (0);
}
