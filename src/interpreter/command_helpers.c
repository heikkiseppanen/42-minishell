/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:55:14 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/09 15:01:28 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_main	get_sub_process(char **argv)
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

	if (!argv || !*argv)
		return (NULL);
	executor = ft_htable_get(&table, argv[0]);
	if (!executor)
	{
		return (launch_executable);
	}
	return (executor);
}

int	execute_locally(t_main process, char **argv, t_ast_node *redir)
{
	const int	std_in = dup(STDIN_FILENO);
	const int	std_out = dup(STDOUT_FILENO);
	const int	std_err = dup(STDERR_FILENO);
	int			exit_status;

	register_handler(HANDLER_DFL);
	exit_status = 0;
	if (perform_redirections(redir) == MS_SUCCESS)
	{
		if (argv && *argv)
		{
			exit_status = process(argv);
		}
	}
	else
	{
		exit_status = 1;
	}
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	dup2(std_err, STDERR_FILENO);
	close(std_in);
	close(std_out);
	close(std_err);
	return (exit_status);
}

pid_t	create_fork(t_pipe *in, t_pipe *out, t_ast_node *redir)
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
		if (in != NULL && !pipe_connect(in->read, STDIN_FILENO, in->write))
			exit(1);
		if (out != NULL && !pipe_connect(out->write, STDOUT_FILENO, out->read))
			exit(1);
		if (!perform_redirections(redir))
			exit(1);
	}
	return (process);
}

int	process_exit_status(int exit_status, int builtin, char **const argv)
{
	ft_strarr_del(argv);
	if (builtin)
		return (exit_status);
	if (WIFSIGNALED(exit_status))
	{
		write(1, "\n", 1);
		return (WTERMSIG(exit_status) + 128);
	}
	return (WEXITSTATUS(exit_status));
}
