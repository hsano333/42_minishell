/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:14:38 by hsano             #+#    #+#             */
/*   Updated: 2022/11/04 04:51:37 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HEREDOC_H
# define PARSER_HEREDOC_H
# define HEREDODC_FILE ".heredoc"
# include "pipex.h"
# include "libft_str.h"
# include "libft_put.h"
# include "parser.h"
# include "parser_util.h"
# include "parser_expand.h"
# include "signal_minishell.h"

int	create_heredoc_file(t_token *tokens);
#endif
