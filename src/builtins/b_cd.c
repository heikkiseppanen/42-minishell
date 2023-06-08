/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:07:10 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/23 17:16:16 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include "libft.h"
#include "minishell.h"

static int	error_return(char *old_pwd)
{
	if (old_pwd)
		free(old_pwd);
	perror("minishell: cd");
	return (1);
}

static char	*get_pwd(void)
{
	extern t_shell_state	g_state;
	char					*pwd;
	char					*tmp;
	char					buf[4097];

	pwd = ft_htable_get(g_state.envp, "PWD");
	if (!pwd)
	{
		getcwd(buf, 4096);
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
		return (0);
	perror("minishell: cd");
	return (1);
}

static int	update_env(char *old_pwd, char *buf)
{
	extern t_shell_state	g_state;

	ft_htable_insert(g_state.envp, "OLDPWD", old_pwd);
	ft_htable_insert(g_state.envp, "PWD", buf);
	if (!old_pwd || !buf)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	change_directory(char **argv)
{
	DIR		*t_dir;
	char	buf[4097];
	char	*old_pwd;

	old_pwd = get_pwd();
	if (!old_pwd)
		return (error_return(NULL));
	if (!argv[1])
	{
		if (!go_home())
			return (1);
	}
	else
	{
		t_dir = opendir(argv[1]);
		if (!t_dir)
			return (error_return(NULL));
		if (chdir(argv[1]) != 0)
			return (error_return(old_pwd));
		closedir(t_dir);
	}
	getcwd(buf, 4096);
	return (update_env(ft_strdup(old_pwd), ft_strdup(buf)));
}
