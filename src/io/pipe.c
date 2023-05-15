/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:49:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/08 14:59:20 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

#include <unistd.h>
#include <stdio.h>

e_err	pipe_init(t_pipe *empty)
{
	if (pipe((int *)empty) == -1)
	{
		perror("Failed to open pipe");
		empty->read = -1;
		empty->write = -1;
		return (MS_FAIL);
	}
	return (MS_SUCCESS);
}

e_err	pipe_close(t_pipe *pipe)
{
	if (close(pipe->read) == -1)
	{
		perror("Failed to close pipe read end");
		return (MS_FAIL);
	}
	if (close(pipe->write) == -1)
	{
		perror("Failed to close pipe write end");
		return (MS_FAIL);
	}
	return (MS_SUCCESS);
}

e_bool	pipe_is_valid(t_pipe *pipe)
{
	return (pipe->read > 0 && pipe->write > 0);
}

e_err	pipe_connect(int source, int target, int unused)
{
	if (dup2(source, target) == -1)
	{
		perror("Failed to connect pipe end");
		return (MS_FAIL);
	}
	if (close(source) == -1)
	{
		perror("Failed to close source end");
		return (MS_FAIL);
	}
	if (close(unused) == -1)
	{
		perror("Failed to close unused end");
		return (MS_FAIL);
	}
	return (MS_SUCCESS);
}
