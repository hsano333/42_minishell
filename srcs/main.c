/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/11/04 22:14:16 by maoyagi          ###   ########.fr       */
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
#include "lexer_continue_input.h"

static char *analyze_and_execute(char *line)
{
	t_token *tokens;
	t_cmds *cmds;

	tokens = lexer(line);
	if (tokens)
	{
		while (tokens && is_continue_input(tokens))
			tokens = continued_input(tokens, &line);
		if (!tokens)
			return (line);
		cmds = parser(tokens);
		exe_cmds(cmds);
		clear_tokens(tokens);
		clear_all_cmds(&cmds);
	}
	return (line);
}

//簡易的な入力受付
int loop()
{
	char *line;
	int exit_code;

	exit_code = 0;
	while (true)
	{
		line = readline("\033[31mminishell$ \033[0m");
		// NULLポインタ
		if (!line)
		{
			printf("exit\n");
			free(line);
			break;
		}
		// NULL文字
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		line = analyze_and_execute(line);
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
	// t_env *env;
	char **envv;

	(void)argc;
	(void)argv;

	// char **に後で変更する
	// env = init_env(envp); //後で消す
	// set_signal(DEFAULT_MODE);
	handle_global_signals();
	envv = str_arr_dup(envp);
	// env_store(envv, INIT_ENV);
	initialize_env(envv);

	if (is_builtin(&argv[1]))
	{
		exec_builtin_cmd(&argv[1]);
		//  cmd_env(&argv[1]);
		//  cmd_pwd();
		//  cmd_export(&argv[1]);
		//  cmd_unset(&argv[1]);
		//  cmd_cd(&argv[1]);
		//  cmd_exit(&argv[1]);
		print_env2((const char **)env_store(NULL, GET_ENV));
	}

	// readline
	loop();

	// free_env(env);
	envv = env_store(NULL, GET_ENV);
	free_str_array(&envv);
	// system("leaks minishell");

	return (0);
}
