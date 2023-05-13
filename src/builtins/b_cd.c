/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:07:10 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/13 04:11:02 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

extern t_shell_state	g_state; 

int	change_directory(char	**argv)
{
	struct stat	info;
	int			fd;
	char		*buf;

	fd = open(argv[1], O_RDONLY); 
	fstat(fd, &info);
	buf = malloc(1024);
	close(fd);
	if (!buf)
		return (1);
	if (S_ISDIR(info.st_mode))
	{
		chdir(argv[1]);
		getcwd(buf, 1024);
		ft_htable_insert(g_state.envp, "PWD", buf);
	}
	else
	{
		free(buf);
		return (1);
	}
	return (0);
}

