/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 01:55:22 by hsano             #+#    #+#             */
/*   Updated: 2022/11/19 21:22:32 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_BUILTIN_H
# define CMD_BUILTIN_H

int	exec_builtin_cmd(char **cmd);
int	builtin_wrapper(char **cmd, t_pipe *pipe_info);
int	is_builtin(char **cmd);
#endif
