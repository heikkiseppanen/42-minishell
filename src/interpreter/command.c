/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:39:41 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/11 11:06:55 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "redir.h"
#include "builtins.h"
#include "expand.h"
#include "sys/wait.h"

#include <stdio.h>

static t_main	get_sub_process(const char *arg0)
{
	static t_htelem		elements[] = {
		{"echo", echo},
		{"cd", change_directory},
		{"pwd", put_cwd},
		{"env", put_env},
		{"export", export_var},
		{"unset", unset_var}};
	static t_htelem		*pointers[] = {
		&elements[0],
		&elements[1],
		&elements[2],
		&elements[3],
		&elements[4]};
	static t_htable		table = {pointers, 5, 5};
	const t_main	executor = ft_htable_get(&table, arg0);

	if (!executor)
	{
		return (launch_executable);
	}
	return (executor);
}

pid_t	launch_command(t_ast_node *command, t_pipe *in, t_pipe *out)
{
	const pid_t	process = fork();
	char		**argv;

	if (process == -1)
	{
		perror("Failed to fork process");
	}
	else if (process == 0)
	{
		if (in != NULL)
			pipe_connect(in->read, STDIN_FILENO, in->write);
		if (out != NULL)
			pipe_connect(out->write, STDOUT_FILENO, out->read);
		argv = expand_arglist(ast_left(command)->data.args.argv);
		if (!argv)
		{
			exit(1);
		}
		perform_redirections(ast_right(command));
		exit(get_sub_process(argv[0])(argv));
	}
	return (process);
}

int	execute_command(t_ast_node *command)
{
	char **const	argv = expand_arglist(ast_left(command)->data.args.argv);
	const t_main	sub_process = get_sub_process(argv[0]);
	pid_t			process;
	int				exit_status;

	if (sub_process == launch_executable)
	{
		process = fork();
		if (process == -1)
		{
			return (1);
		}
		if (process == 0)
		{
			perform_redirections(ast_right(command));
			exit(sub_process(argv));
		}
		waitpid(process, &exit_status, 0);
	}
	else
	{
		exit_status = sub_process(argv);
	}
	ft_strarr_del(argv);
	return (WEXITSTATUS(exit_status));
}
