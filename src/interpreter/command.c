/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:39:41 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/18 22:26:41 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "redir.h"
#include "builtins.h"
#include "expand.h"
#include "sys/wait.h"
#include "sig.h"
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
		&elements[4],
		&elements[5]};
	static t_htable		table = {pointers, 6, 6};
	if (!arg0)
		return (NULL);
	const t_main	executor = ft_htable_get(&table, arg0);

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
	int	exit_status;

	dfl_handler();
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

pid_t	launch_command(t_ast_node *command, t_pipe *in, t_pipe *out)
{
	ign_handler();
	const pid_t	process = fork();
	char		**argv;

	if (process == -1)
	{
		perror("Failed to fork process");
	}
	else if (process == 0)
	{
		dfl_handler();
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
	t_main			sub_process;
	pid_t			process;
	int				exit_status;

	if (!argv)
		return (0);
	sub_process = get_sub_process(argv[0]);
	if (sub_process == launch_executable)
	{
		ign_handler();
		process = fork();
		if (process == -1)
			return (1);
		if (process == 0)
		{
			dfl_handler();
			perform_redirections(ast_right(command));
			exit(sub_process(argv));
		}
		waitpid(process, &exit_status, 0);
	}
	else
	{
		return(execute_locally(sub_process, argv, ast_right(command)));
	}
	ft_strarr_del(argv);
	if (WIFSIGNALED(exit_status))
	{
		write(1, "\n", 1);
		return (WTERMSIG(exit_status) + 128);
	}
	return (WEXITSTATUS(exit_status));
}
