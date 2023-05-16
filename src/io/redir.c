/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:10:16 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/16 10:29:12 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

#include "pipe.h"

#include <libft.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	redir_del(t_redir *instances, int size)
{
	t_redir	*it;

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

static int	open_basic_file(const char *path, int flags)
{
	const int	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	const int	file = open(path, flags, mode);

	if (file == -1)
	{
		perror(path);
	}
	return (file);
}

static int	open_here_doc(const char *here_doc)
{
	t_pipe	file;

	if (!pipe_init(&file))
	{
		return (-1);
	}
	write(file.write, here_doc, ft_strlen(here_doc));
	close(file.write);
	return (file.read);
}

e_err	redir_execute(const t_redir *redir)
{
	int	file;

	file = -1;
	if (redir->operation == REDIR_OUT_APPEND)
	{
		file = open_basic_file(redir->argument, O_CREAT | O_WRONLY | O_APPEND);
	}
	else if (redir->operation == REDIR_OUT_TRUNC)
	{
		file = open_basic_file(redir->argument, O_CREAT | O_WRONLY | O_TRUNC);
	}
	else if (redir->operation == REDIR_IN_FILE)
	{
		file = open_basic_file(redir->argument, O_RDONLY);
	}
	else if (redir->operation == REDIR_IN_HEREDOC)
	{
		file = open_here_doc(redir->argument);
	}
	if (file == -1
		|| dup2(file, redir->file_descriptor) == -1 || close(file) == -1)
	{
		return (MS_FAIL);
	}
	return (MS_SUCCESS);
}
