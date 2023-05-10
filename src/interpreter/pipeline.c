/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:50:23 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/09 11:43:28 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

#include <stdlib.h>
#include <sys/wait.h>

static e_err	pipe_cmd(t_ast_node *cmd, t_pipe *in, t_pipe *out, t_buf *pid)
{
	pid_t	process;

	process = launch_command(cmd, in, out);
	if (process <= 0 || !buf_pushback(pid, &process, 1))
	{
		return (MS_FAIL);
	}
	return (MS_SUCCESS);
}

e_err	launch_pipeline(t_ast_node *pipe, t_pipe *input, t_buf *pid_out)
{
	t_pipe	output;
	e_err	status;

	pipe_init(&output);
	if (pipe_cmd(ast_left(pipe), input, &output, pid_out) == MS_FAIL)
	{
		return (MS_FAIL);
	}
	if (input)
	{
		pipe_close(input);
	}
	pipe = ast_right(pipe);
	if (pipe->type == AST_PIPE)
	{
		status = launch_pipeline(pipe, &output, pid_out);
	}
	else if (pipe->type == AST_COMMAND)
	{
		status = pipe_cmd(pipe, &output, NULL, pid_out);
		pipe_close(&output);
	}
	else
		status = MS_FAIL;
	return (status);
}

e_err	execute_pipeline(t_ast_node *pipeline_start)
{
	t_buf	processes;

	if (!buf_init(&processes, 2, sizeof(pid_t))
		|| launch_pipeline(pipeline_start, NULL, &processes) == MS_FAIL)
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
		++proc_it;
	}

	buf_del(&processes);
	return (MS_SUCCESS);
}