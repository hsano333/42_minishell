/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/11/07 04:45:22 by hsano            ###   ########.fr       */
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

static char	*analyze_and_execute(char *line)
{
	t_token	*tokens;
	t_cmds	*cmds;

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

int	loop(void)
{
	char	*line;
	int		exit_code;

	exit_code = 0;
	while (true)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			free(line);
			break ;
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		line = analyze_and_execute(line);
		free(line);
	}
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envv;

	(void)argc;
	(void)argv;
	handle_global_signals();
	envv = str_arr_dup(envp);
	initialize_env(envv);
	loop();
	envv = env_store(NULL, GET_ENV);
	free_str_array(&envv);
	return (0);
}
