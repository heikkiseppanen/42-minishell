/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:07:10 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/13 05:06:10 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

extern t_shell_state	g_state; 

int	go_to_dir(struct stat info, char **argv, char *buf)
{
	char	*old_pwd = ft_strdup(ft_htable_get(g_state.envp, "PWD"));

	old_pwd = ft_strdup(ft_htable_get(g_state.envp, "PWD"));
	if (S_ISDIR(info.st_mode) && old_pwd)
	{
		if (chdir(argv[1]) != 0)
		{
			perror("cd");
			free(buf);
			return (1);
		}
		getcwd(buf, 1024);
		ft_htable_insert(g_state.envp, "PWD", buf);
		ft_htable_insert(g_state.envp, "OLDPWD", old_pwd);
	}
	else
	{
		perror("cd");
		free(buf);
		return (1);
	}
	return (0);
}

int	change_directory(char	**argv)
{
	struct stat	info;
	int			fd;
	char		*buf;

	fd = open(argv[1], O_RDONLY); 
	if (fd == -1)
	{
		perror("cd");
		return (1);
	}
	fstat(fd, &info);
	close(fd);
	buf = malloc(1024);
	if (!buf || go_to_dir(info, argv, buf))
		return (1);
	return (0);
}

