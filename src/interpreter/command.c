/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:39:41 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/24 12:23:41 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "redir.h"
#include "builtins.h"
#include "expand.h"
#include "sys/wait.h"
#include "sig.h"
#include <stdio.h>

static t_main	get_sub_process(char **argv)
{
	static t_htelem	elements[] = {
	{"echo", echo},
	{"cd", change_directory},
	{"pwd", put_cwd},
	{"env", put_env},
	{"export", export_var},
	{"exit", exit_cmd},
	{"unset", unset_var}
	};
	static t_htelem	*pointers[] = {
		&elements[0], &elements[1], &elements[2], &elements[3],
		&elements[4], &elements[5], &elements[6]
	};
	static t_htable	table = {pointers, 7, 7};
	t_main			executor;

	if (!argv)
		return (NULL);
	executor = ft_htable_get(&table, argv[0]);
	if (!executor)
	{
		return (launch_executable);
	}
	return (executor);
}

static int	execute_locally(t_main process, char **argv, t_ast_node *redir)
{
	const int	std_in = dup(STDIN_FILENO);
	const int	std_out = dup(STDOUT_FILENO);
	const int	std_err = dup(STDERR_FILENO);
	int			exit_status;

	register_handler(HANDLER_DFL);
	exit_status = 0;
	if (perform_redirections(redir) == MS_SUCCESS)
	{
		exit_status = process(argv);
	}
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	dup2(std_err, STDERR_FILENO);
	close(std_in);
	close(std_out);
	close(std_err);
	return (exit_status);
}

static pid_t	create_fork(t_pipe *in, t_pipe *out, t_ast_node *redir)
{
	pid_t	process;

	register_handler(HANDLER_IGN);
	process = fork();
	if (process == -1)
	{
		perror("minishell: Failed to fork");
	}
	if (process == 0)
	{
		register_handler(HANDLER_DFL);
		if (in != NULL)
			pipe_connect(in->read, STDIN_FILENO, in->write);
		if (out != NULL)
			pipe_connect(out->write, STDOUT_FILENO, out->read);
		perform_redirections(redir);
	}
	return (process);
}

pid_t	launch_command(t_ast_node *command, t_pipe *in, t_pipe *out)
{
	const pid_t	process = create_fork(in, out, ast_right(command));
	char		**argv;
	t_main		sub_process;

	if (process == 0)
	{
		argv = expand_arglist(ast_left(command)->data.args.argv);
		if (!argv)
		{
			exit (1);
		}
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
		exit_status = execute_locally(sub_process, argv, ast_right(command));
	ft_strarr_del(argv);
	if (WIFSIGNALED(exit_status))
	{
		write(1, "\n", 1);
		return (WTERMSIG(exit_status) + 128);
	}
	return (WEXITSTATUS(exit_status));
}
