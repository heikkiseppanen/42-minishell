/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:58:38 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/01 08:58:20 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "ast.h"
#include "pipe.h"
#include "redirection.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

e_err	perform_redirections(t_ast_node *redirections)
{
	t_redir	*it;
	t_redir	*end;

	if (redirections->type != AST_REDIR)
		return (MS_FAIL);
	it = redirections->data.redir.array;
	end = it + redirections->data.redir.size;
	while (it != end)
	{
		if (redir_execute(it) == MS_FAIL)
		{
			return (MS_FAIL);
		}
		++it;
	}
	return (MS_SUCCESS);
}

pid_t	launch_command(t_ast_node *command, t_pipe *in, t_pipe *out)
{
	const pid_t			process = fork();
	t_ast_args *const	arguments = &ast_left(command)->data.args;

	if (process == -1)
	{
		perror("Failed to fork process");
	}
	else if (process == 0)
	{
		if (in != NULL)
		{
			pipe_connect(in->read, STDIN_FILENO, in->write);
		}
		if (out != NULL)
		{
			pipe_connect(out->write, STDOUT_FILENO, out->read);
		}
		perform_redirections(ast_right(command));
		execve(arguments->argv[0], arguments->argv, NULL);
		perror("Failed to execute command");
		exit(127);
	}
	return (process);
}

e_err	execute_command(t_ast_node *command)
{
	pid_t				process;
	int					exit_status;

	process = launch_command(command, NULL, NULL);
	if (process == -1)
	{
		return (MS_FAIL);
	}
	waitpid(process, &exit_status, 0);
	printf("Process exited with code: %d\n", WEXITSTATUS(exit_status));
	return (MS_SUCCESS);
}

e_err	launch_pipeline(t_ast_node *pipeline, t_buf *pid_out)
{
	t_pipe	input;
	t_pipe	output;
	pid_t	process;

	pipe_init(&output);
	process = launch_command(ast_left(pipeline), NULL, &output);
	buf_pushback(pid_out, &process, 1);
	pipeline = ast_right(pipeline);
	while (pipeline->type == AST_PIPE)
	{
		input = output;
		pipe_init(&output);
		process = launch_command(ast_left(pipeline), &input, &output);
		buf_pushback(pid_out, &process, 1);
		pipe_close(&input);
		pipeline = ast_right(pipeline);
	}
	process = launch_command(pipeline, &output, NULL);
	buf_pushback(pid_out, &process, 1);
	pipe_close(&output);
	return (MS_SUCCESS);
}

e_err	execute_pipeline(t_ast_node *pipeline_start)
{
	t_buf	processes;

	if (!buf_init(&processes, 2, sizeof(pid_t))
		|| launch_pipeline(pipeline_start, &processes) == MS_FAIL)
	{
		buf_del(&processes);
		return (MS_FAIL);
	}

	pid_t *proc_it = processes.data;
	pid_t *proc_end = proc_it + processes.size;

	while (proc_it != proc_end)
	{
		int exit_status = 0;

		waitpid(*proc_it, &exit_status, 0);
		printf("Process exited with code: %d\n", exit_status >> 8);
		++proc_it;
	}

	buf_del(&processes);
	return (MS_SUCCESS);
}

e_err	interpret_ast(t_ast_node *node)
{
	if (node->type == AST_PIPE)
	{
		return execute_pipeline(node);
	}
	if (node->type == AST_COMMAND)
	{
		return execute_command(node);
	}
	return (MS_FAIL);
}
