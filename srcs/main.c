/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:31:44 by hsano             #+#    #+#             */
/*   Updated: 2022/11/18 02:27:07 by hsano            ###   ########.fr       */
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

	tokens = lexer(line);
	if (tokens)
	{
		while (tokens && is_continue_input(tokens))
			tokens = continued_input(tokens, &line);
		if (!tokens)
			return (line);
		exe_cmds(tokens);
		clear_tokens(tokens);
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
		if (*line == '\0' || ft_is_str_space(line))
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

void	update_shlvl(void)
{
	char	*shlvl_var;
	char	*shlvl;
	size_t	shlvl_val;
	int		overflow;

	shlvl = get_env_val("SHLVL");
	shlvl_val = (size_t)ft_atol(shlvl, &overflow);
	shlvl_val++;
	if (1000 <= shlvl_val)
	{
		ft_putstr_fd(\
			"bash: warning: shell level (1000) too high, resetting to 1\n", \
		2);
		shlvl_val = 1;
	}
	free(shlvl);
	shlvl = ft_itoa(shlvl_val);
	shlvl_var = ft_strjoin("SHLVL=", shlvl);
	set_env_var(shlvl_var);
	free(shlvl);
	free(shlvl_var);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envv;

	(void)argc;
	(void)argv;
	handle_global_signals();
	envv = str_arr_dup(envp);
	initialize_env(envv);
	update_shlvl();
	loop();
	envv = env_store(NULL, GET_ENV);
	free_str_array(&envv);
	return (0);
}
