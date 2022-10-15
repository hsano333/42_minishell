/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:37:23 by hsano             #+#    #+#             */
/*   Updated: 2022/10/15 14:07:29 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_EXPAND_H
# define PARSER_EXPAND_H
void	expand_doller(t_token *token, token_type pre_token);
size_t	expand_asterisk(t_token *tokens, token_type pre_token);
int	parser_expand(t_token *tokens);

#endif
