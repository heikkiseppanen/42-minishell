/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:59:51 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/02 18:47:18 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "../third-party/libft/libft.h"

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
		echo_str = ft_strjoin(echo_str, " " );
		echo_str = ft_strjoin(echo_str, argv[i]);
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
	char	**var_val;

	var_val = ft_split(argv[1], '=');
	if (!var_val || !var_val[1])
		return (1);
	setenv(var_val[0], var_val[0], 1);
	return (0);
}

int	put_env(char	**argv)
{
	int	i;
	extern char	**environ;

	(void)argv;
	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
