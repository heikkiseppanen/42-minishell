/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:07:10 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/18 22:27:12 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "libft.h"
#include "minishell.h"

extern t_shell_state	g_state;

int	error_return(char *buf)
{
	if (buf)
		free(buf);
	perror("minishell: cd");
	return (-1);
}

int	go_to_dir(char **argv, char *buf)
{
	char	*old_pwd;

	old_pwd = ft_htable_get(g_state.envp, "PWD");
	if (!old_pwd)
		return (error_return(buf));
	old_pwd = ft_strdup(ft_htable_get(g_state.envp, "PWD"));
	if (!old_pwd)
		return (error_return(buf));
	if (!opendir(argv[1]))
		return (error_return(buf));
	if (chdir(argv[1]) != 0)
		return (error_return(buf));
	getcwd(buf, 1024);
	ft_htable_insert(g_state.envp, "PWD", buf);
	ft_htable_insert(g_state.envp, "OLDPWD", old_pwd);
	return (0);
}

int	change_directory(char **argv)
{
	char		*buf;

	buf = malloc(1024);
	if (!buf)
		return (1);
	if (go_to_dir(argv, buf) == -1)
		return (1);
	return (0);
}
