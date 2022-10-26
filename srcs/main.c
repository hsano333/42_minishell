/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/26 08:28:41 by maoyagi          ###   ########.fr       */
=======
/*   Updated: 2022/10/24 23:05:45 by hsano            ###   ########.fr       */
>>>>>>> 419ac6356c78aae2a6f21c150125cdbb90609477
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"
#include "lexer.h"
#include "lexer_util.h"
#include "env.h"
#include "parser.h"
#include "parser_util.h"
#include "parser_expand.h"
#include "parser_heredoc.h"
#include "exe_cmds.h"
#include "dir.h"

//簡易的な入力受付
int loop(t_env *env)
{
	char *line;
	int exit_code;
	t_token *tokens;
	t_cmds *cmds;

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
		// parser_expand(tokens);
		// create_heredoc_file(tokens);
		cmds = parser(tokens);
		exe_cmds(cmds);

		put_tokens(tokens);
		clear_tokens(tokens);
		clear_all_cmds(&cmds);
		// clear_all_cmds(cmds);
		printf("\n");

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

	// printf("env get test:%s\n", env_func(NULL, 1, NULL, NULL));

	//// get
	// printf("env get test:%s\n", env_func(NULL, GET_ENV, "OLDPWD", NULL));
	//存在しないケース
	// printf("env get test:%s\n", env_func(NULL, GET_ENV, "OLDPWDaaaa", NULL));

	// set
	// env_func(NULL, SET_ENV, "test=test", NULL);
	// set_env_var(&env->env_var, "test==test");
	// printf("env get test:%s\n", env_func(NULL, GET_ENV, "test", NULL));
	// print_env2((const char **)envv);
	// print_env(env);

	// del
	// del_env_var(env->env_var, "test1");
	// print_env(env);
	// del_env_var(env->env_var, "test");
	// del_env_var(env->env_var, "test");
	// print_env2((const char **)envp);
	// env_func(NULL, DEL_ENV, "test", NULL);
	// print_env(env);
	// print_env2((const char **)envv);
	// printf("env get test:%s\n", env_func(NULL, GET_ENV, "PWD", NULL));

	cmd_env("env");
	// readline
	loop(env);

	free_env(env);
	free_str_array(&envv);
	// system("leaks minishell");

	return (0);
}
