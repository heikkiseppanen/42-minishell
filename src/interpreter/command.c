/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:39:41 by hseppane          #+#    #+#             */
/*   Updated: 2023/06/09 15:01:02 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

pid_t	launch_command(t_ast_node *command, t_pipe *in, t_pipe *out)
{
	const pid_t	process = create_fork(in, out, ast_right(command));
	char		**argv;
	t_main		sub_process;

	if (process == 0)
	{
		argv = expand_arglist(ast_left(command)->data.args.argv);
		sub_process = get_sub_process(argv);
		exit(sub_process(argv));
	}
	return (process);
}

int	execute_command(t_ast_node *command)
{
	char **const	argv = expand_arglist(ast_left(command)->data.args.argv);
	const t_main	sub_process = get_sub_process(argv);
	pid_t			process;
	int				exit_status;
	int				builtin;

	builtin = 0;
	if (sub_process == launch_executable)
	{
		register_handler(HANDLER_IGN);
		process = create_fork(NULL, NULL, ast_right(command));
		if (process == 0)
		{
			register_handler(HANDLER_DFL);
			exit(sub_process(argv));
		}
		waitpid(process, &exit_status, 0);
	}
	else
	{
		builtin = 1;
		exit_status = execute_locally(sub_process, argv, ast_right(command));
	}
	return (process_exit_status(exit_status, builtin, argv));
}
