/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:59:51 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/03 15:17:58 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

int	change_directory(char	**argv)
{
	chdir(argv[1]);
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
	getcwd(buf, 1024);
	printf("%s\n", buf);
	if (buf)
		free(buf);
	return (0);
}

int	export_var(char **argv)
{
	char					**var_val;
	extern t_shell_state	g_state;

	var_val = ft_split(argv[1], '=');
	if (!var_val || !var_val[1])
		return (1);
	ft_htable_insert(g_state.envp, var_val[0], var_val[1]);
	ft_printf("export %p\n", g_state.environ_copy);
	g_state.environ_copy = htable_to_environ(g_state.envp);
	ft_printf("export %p\n", g_state.environ_copy);
	return (0);
}

int	put_env(char	**argv)
{
	int	i;
	extern t_shell_state g_state;

	(void)argv;
	i = 0;
	ft_printf("env %p\n", g_state.environ_copy);
	while (g_state.environ_copy[i])
	{
		printf("%s\n", g_state.environ_copy[i]);
		i++;
	}
	return (0);
}
