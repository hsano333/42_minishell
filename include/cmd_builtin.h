/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 01:55:22 by hsano             #+#    #+#             */
/*   Updated: 2022/11/03 21:40:19 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_BUILTIN_H
# define CMD_BUILTIN_H

int	exec_builtin_cmd(char **cmd);
int	is_builtin(char **cmd);
int	not_use_piped(char **cmd);
#endif

