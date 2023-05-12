/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:10:16 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/16 08:52:32 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	redir_del(t_redir *instances, int size)
{
	t_redir *it;

	if (!instances || !size)
		return ;
	it = instances;
	while (size--)
	{
		if (it->argument)
		{
			free((void *)it->argument);
		}
		++it;
	}
	free(instances);
}

#include "pipe.h"
#include <readline/readline.h>
#include <libft.h>

e_err	redir_execute(const t_redir *instance)
{
	if (instance->operation == REDIR_OUT_APPEND)
	{
		const int flags = O_CREAT | O_WRONLY | O_APPEND;
		const int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
		const int file = open(instance->argument, flags, mode);

		if (file < 0)
		{
			perror(instance->argument);
			return (MS_FAIL);
		}
		if (dup2(file, instance->file_descriptor) == -1 || close(file) == -1)
			perror("redir error");
		return (MS_SUCCESS);
	}
	else if (instance->operation == REDIR_OUT_TRUNC)
	{
		const int flags = O_CREAT | O_WRONLY | O_TRUNC;
		const int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
		const int file = open(instance->argument, flags, mode);

		if (file < 0)
		{
			perror(instance->argument);
			return (MS_FAIL);
		}
		if (dup2(file, instance->file_descriptor) == -1 || close(file) == -1)
			perror("redir error");
		return (MS_SUCCESS);
	}
	else if (instance->operation == REDIR_IN_FILE)
	{
		const int flags = O_RDONLY;
		const int file = open(instance->argument, flags);

		if (file < 0)
		{
			perror(instance->argument);
			return (MS_FAIL);
		}
		dup2(file, instance->file_descriptor);
		close(file);
		return (MS_SUCCESS);
	}
	else if (instance->operation == REDIR_IN_HEREDOC)
	{
		t_pipe	here_doc;

		if (!pipe_init(&here_doc))
			return (MS_FAIL);
		write(here_doc.write, instance->argument, ft_strlen(instance->argument));
		pipe_connect(here_doc.read, instance->file_descriptor, here_doc.write);
		return (MS_SUCCESS);
	}
	return (MS_SUCCESS);
}

