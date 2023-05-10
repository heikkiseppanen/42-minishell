/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:59:51 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/10 03:03:12 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include "minishell.h"
extern t_shell_state	g_state; 

int	change_directory(char	**argv)
{
	struct stat				info;
	int						fd;
	char					*buf;

	fd = open(argv[1], O_RDONLY); 
	fstat(fd, &info);
	buf = malloc(1024);
	if (!buf)
		return (1);
	if (S_ISDIR(info.st_mode))
	{
		getcwd(buf, 1024);
		buf = ft_strjoin(buf, "/");
		buf = ft_strjoin(buf, argv[1]);
		chdir(argv[1]);
		getcwd(buf, 1024);
		ft_htable_insert(g_state.envp, "PWD", buf);
	}
	else
	{
		printf("cd: not a directory: %s\n", argv[1]);
		free(buf);
		return (1);
	}
	printf("env changed: %s\n", (char *)ft_htable_get(g_state.envp, "PWD"));
	return (0);
}

int	echo(char **argv)
{
	char	*echo_str;
	int		nline_flag;
	int		i;

	i = 1;
	nline_flag = 0;
	echo_str = "";
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], "-n", 2) && i == 1)
		{
			nline_flag = 1;
			i++;
			continue ;
		}
		echo_str = ft_strjoin(echo_str, argv[i]);
		if (argv[i + 1])
			echo_str = ft_strjoin(echo_str, " " );
		i++;
	}
	if (nline_flag)
		printf("%s", echo_str);
	else
		printf("%s\n", echo_str);
	return (0);
}

int	put_cwd(char **argv)
{
	char	*buf;

	(void)argv;
	buf = malloc(1024);
	if (!buf)
		return (1);
	getcwd(buf, 1024);
	printf("%s\n", buf);
	if (buf)
		free(buf);
	return (0);
}

int	put_env(char	**argv)
{
	size_t					i;
	extern t_shell_state	g_state;

	(void)argv;
	i = 0;
	while (i < g_state.envp->cap)
	{
		if (g_state.envp->memory[i])
			ft_printf("%s=%s\n", g_state.envp->memory[i]->key, g_state.envp->memory[i]->value);
		i++;
	}
	return (0);
}

int	export_var(char **argv)
{
	char					**var_val;
	extern t_shell_state	g_state;
	int						cur_arg;

	cur_arg = 1;
	if (!argv[cur_arg])
		put_env(argv);
	while (argv[cur_arg])
	{
		var_val = ft_split(argv[1], '=');
		if (!var_val || !var_val[0])
			return (1);
		if (!var_val[1])
			ft_htable_insert(g_state.envp, var_val[0], "");
		else
			ft_htable_insert(g_state.envp, var_val[0], var_val[1]);
		cur_arg++;
	}
	return (0);
}

int	unset_var(char	**argv)
{
	extern t_shell_state	g_state;

	(void)argv;
	ft_htable_remove(g_state.envp, argv[1]);
	return (0);
}
