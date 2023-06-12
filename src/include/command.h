/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:56:12 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/12 11:26:02 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "interpreter.h"
# include "redir.h"
# include "builtins.h"
# include "expand.h"
# include "sys/wait.h"
# include "sig.h"
# include <stdio.h>

t_main	get_sub_process(char **argv);
int		execute_locally(t_main process, char **argv, t_ast_node *redir);
pid_t	create_fork(t_pipe *in, t_pipe *out, t_ast_node *redir);
int		process_exit_status(int exit_status, int builtin, char **const argv);

#endif
