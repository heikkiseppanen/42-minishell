/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:55:58 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/11 09:28:04 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H

# include "typedef.h"
# include "ast.h"
# include "pipe.h"

typedef int (*t_main)(char **);

e_err	interpret_ast(t_ast_node *node);

int		execute_pipeline(t_ast_node *pipeline_start);
int		execute_command(t_ast_node *command);

e_err	launch_pipeline(t_ast_node *pipe, t_pipe *input, t_buf *pid_out);
pid_t	launch_command(t_ast_node *command, t_pipe *in, t_pipe *out);
int		launch_executable(char **argv);
//
e_err	perform_redirections(t_ast_node *redirections);

#endif
