/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/10/28 16:13:38 by hsano            ###   ########.fr       */
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
#include "kill_myprocess.h"


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
		cmds = parser(tokens);
		exe_cmds(cmds);

		//put_tokens(tokens);
		clear_tokens(tokens);
		clear_all_cmds(&cmds);
		//kill_myprocess(-1, NULL, tokens, cmds);
		// clear_all_cmds(cmds);
		//printf("\n");

		//printf("%s\n", line);
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
	env_store(envv, INIT_ENV);

	print_env2((const char **)env_store(NULL, GET_ENV));
	//printf("env get test:%s\n", get_env_val("USER"));
	set_env_var("test=test");
	print_env2((const char **)env_store(NULL, GET_ENV));
	del_env_var("test");
	print_env2((const char **)env_store(NULL, GET_ENV));
	set_env_var("test=test");

	set_env_var("test=test2");
	print_env2((const char **)env_store(NULL, GET_ENV));

	// readline
	loop(NULL);

	free_env(env);
	envv = env_store(NULL, GET_ENV);
	free_str_array(&envv);
	// system("leaks minishell");

	return (0);
}
