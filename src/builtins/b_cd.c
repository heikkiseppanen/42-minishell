/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:07:10 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/12 10:11:29 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "minishell.h"

static int	error_return(char *old_pwd, int perror_print)
{
	if (old_pwd)
		free(old_pwd);
	if (perror_print)
		perror("minishell: cd");
	return (1);
}

static char	*get_pwd(void)
{
	extern t_shell_state	g_state;
	char					*pwd;
	char					*tmp;
	char					buf[DIR_MAX];

	pwd = ft_htable_get(g_state.envp, "PWD");
	if (!pwd)
	{
		getcwd(buf, DIR_MAX - 1);
		tmp = ft_strdup(buf);
		if (!tmp)
			return (NULL);
		ft_htable_insert(g_state.envp, "PWD", tmp);
		pwd = ft_htable_get(g_state.envp, "PWD");
	}
	return (pwd);
}

static int	go_home(void)
{
	extern t_shell_state	g_state;

	if (!ft_htable_get(g_state.envp, "HOME"))
	{
		ft_fprintf(2, "minishell: cd: HOME not set");
		return (0);
	}
	if (chdir(ft_htable_get(g_state.envp, "HOME")) != 0)
	{
		perror("minishell: cd");
		return (0);
	}
	return (1);
}

static int	go_to_dir(char **argv, int *perror_print)
{
	DIR	*t_dir;

	if (!argv[1][0])
	{
		*perror_print = 0;
		return (0);
	}
	*perror_print = 1;
	if (access(argv[1], F_OK) == -1)
		return (0);
	t_dir = opendir(argv[1]);
	if (!t_dir)
		return (0);
	if (chdir(argv[1]) != 0)
	{
		closedir(t_dir);
		return (0);
	}
	closedir(t_dir);
	return (1);
}

int	change_directory(char **argv)
{
	extern t_shell_state	g_state;
	char					buf[DIR_MAX];
	char					*old_pwd;
	int						perror_print;

	old_pwd = get_pwd();
	if (!old_pwd)
		return (error_return(NULL, 1));
	if (!argv[1])
	{
		if (!go_home())
			return (1);
		return (0);
	}
	else if (!go_to_dir(argv, &perror_print))
		return (error_return(NULL, perror_print));
	getcwd(buf, DIR_MAX - 1);
	ft_htable_insert(g_state.envp, "OLDPWD", old_pwd);
	ft_htable_insert(g_state.envp, "PWD", buf);
	if (!old_pwd)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
