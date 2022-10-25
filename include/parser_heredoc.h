/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:14:38 by hsano             #+#    #+#             */
/*   Updated: 2022/10/19 16:09:22 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HEREDOC_H
# define PARSER_HEREDOC_H
# define HEREDODC_FILE ".heredoc"

int	create_heredoc_file(t_token *tokens);
#endif
