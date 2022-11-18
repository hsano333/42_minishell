/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:54:48 by hsano             #+#    #+#             */
/*   Updated: 2022/11/18 15:47:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_heredoc.h"
#include "signal_minishell.h"
#include "exit_status.h"
#include "parser_error.h"
#include "libft_str.h"
#include "token_type.h"

static void	expand_and_write(char *str, int fd)
{
	char	*p;
	char	bk;
	size_t	i;

	i = 0;
	while (str && str[i] && str[i] != '$')
		write(fd, &(str[i++]), 1);
	if (!str[i])
		return ;
	if (str[i] == '$')
		i++;
	p = &(str[i]);
	while (str[i] && is_valid_env_char(str[i]))
		i++;
	bk = str[i];
	str[i] = '\0';
	p = get_env_val(p);
	str[i] = bk;
	ft_putstr_fd(p, fd);
	free(p);
	if (bk == '\0')
		return ;
	expand_and_write(&(str[i]), fd);
}

static int	execute_heredoc_loop(t_heredoc *heredoc \
		, int *fd, int error, char *line)
{
	while (true)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			error = true;
			break ;
		}
		if (*line == '\0' && g_signal_flag && set_exit_status(1))
		{
			g_signal_flag = 0;
			error = true;
			break ;
		}
		if (ft_strncmp(line, heredoc->limiter, ft_strlen(heredoc->limiter) + 1) \
				== 0)
			break ;
		expand_and_write(line, *fd);
		write(*fd, "\n", 1);
		free(line);
	}
	free(line);
	return (error);
}

static int	execute_heredoc(t_token *token, t_heredoc *heredoc, size_t cnt)
{
	int		fd;
	int		error;
	char	*line;
	char	heredoc_file[PATH_MAX + 1];
	char	cnt_str[32];

	ft_itoa_no_memory(cnt, heredoc_file, cnt_str);
	ft_strlcpy(heredoc_file, HEREDODC_FILE, PATH_MAX + 1);
	ft_strlcat(heredoc_file, cnt_str, PATH_MAX + 1);
	line = NULL;
	rl_event_hook = signal_check_state;
	handle_heredoc_signals();
	unlink(heredoc_file);
	fd = open(heredoc_file, O_CREAT | O_WRONLY, 0744);
	if (fd < 0)
		return (false);
	error = false;
	error = execute_heredoc_loop(heredoc, &fd, error, line);
	close(fd);
	fd = open(heredoc_file, O_RDONLY, 0744);
	token->heredoc_fd = fd;
	unlink(heredoc_file);
	handle_global_signals();
	return (!error);
}

static void	get_heredoc_setting(t_heredoc *heredoc, t_token *tokens, size_t i)
{
	heredoc->valid = false;
	if (is_string_token(tokens[i + 1].type))
	{
		if (tokens[i + 1].literal)
		{
			heredoc->limiter = tokens[i + 1].literal;
			heredoc->valid = true;
		}
	}
}

int	create_heredoc_file(t_token *tokens)
{
	size_t		i;
	size_t		cnt;
	t_heredoc	heredoc;

	i = 0;
	cnt = 0;
	while (tokens[i].type != EOS)
	{
		if (!tokens[i].valid)
		{
			i++;
			continue ;
		}
		if (tokens[i].type == D_GT)
		{
			get_heredoc_setting(&heredoc, tokens, i);
			handle_global_signals();
			if (heredoc.valid)
				heredoc.valid = execute_heredoc(&(tokens[i]), &heredoc, cnt++);
			handle_cmd_signals();
		}
		i++;
	}
	return (heredoc.valid);
}
