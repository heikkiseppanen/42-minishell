/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:10:16 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/10 14:37:00 by hseppane         ###   ########.fr       */
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
		//const int flags = O_CREAT | O_WRONLY | O_TRUNC;
		//const int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
		//const int file = open(instance->argument, flags, mode);
		t_pipe	here_doc;

		if (!pipe_init(&here_doc))
			return (MS_FAIL);
		while (1)
		{
			const int	argument_length = ft_strlen(instance->argument);
			char		*line;
			int			line_length;

			line = readline("> ");
			line_length = ft_strlen(line);
			printf("Line: %d Arg: %d", line_length, argument_length);
			if (line_length == argument_length
				&& ft_memcmp(line, instance->argument, argument_length) == 0)
			{
				free(line);
				//write(here_doc.write, "\0", 1);
				break ;
			}
			write(here_doc.write, line, line_length);
			ft_putchar_fd('\n', here_doc.write);
			free(line);
		}
		pipe_connect(here_doc.read, instance->file_descriptor, here_doc.write);
		return (MS_SUCCESS);
	}
	return (MS_SUCCESS);
}

