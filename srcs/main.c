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
	char *line;
	int exit_code;
	t_token *tokens;

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

		// lexer parser
		tokens = lexer(line);
		put_tokens(tokens);
		expand_str(tokens, NON, 0);
		printf("\n");
		put_tokens(tokens);

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
	char **envv;

	(void)argc;
	(void)argv;

	// char **に後で変更する
	env = init_env(envp); //後で消す
	envv = str_arr_dup(envp);

	// print_env(env);
	// env_func(&env->env_var, 0, NULL, NULL);
	env_func(&envv, 0, NULL, NULL);

	printf("env get test:%s\n", env_func(NULL, 1, NULL, NULL));

	// get
	printf("env get test:%s\n", env_func(NULL, GET_ENV, "OLDPWD", NULL));

	// set
	env_func(NULL, SET_ENV, "test=test", NULL);
	// set_env_var(&env->env_var, "test==test");
	printf("env get test:%s\n", env_func(NULL, GET_ENV, "test", NULL));
	print_env2((const char **)envv);
	// print_env(env);

	// del
	// del_env_var(env->env_var, "test1");
	// print_env(env);
	// del_env_var(env->env_var, "test");
	// del_env_var(env->env_var, "test");
	// print_env2((const char **)envp);
	env_func(NULL, DEL_ENV, "test", NULL);
	// print_env(env);
	print_env2((const char **)envv);
	printf("env get test:%s\n", env_func(NULL, GET_ENV, "PWD", NULL));

	// readline
	loop(env);

	free_env(env);
	free_str_array(&envv);
	// system("leaks minishell");

	return (0);
}
