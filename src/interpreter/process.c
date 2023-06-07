/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:59:25 by hseppane          #+#    #+#             */
/*   Updated: 2023/06/07 10:42:30 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "expand.h"
#include "minishell.h"

#include <stdio.h>

static char	*str_extend(char *string, char *extension)
{
	char	*result;

	result = ft_strjoin(string, extension);
	free(string);
	return (result);
}

static char	*expand_executable_path(char *executable_path)
{
	extern t_shell_state	g_state;
	char					**paths;
	char					**it;
	char					*new_path;

	if (access(executable_path, F_OK) == 0)
		return (executable_path);
	paths = ft_split(ft_htable_get(g_state.envp, "PATH"), ':');
	it = paths;
	while (*it)
	{
		new_path = ft_strjoin(*it, "/");
		new_path = str_extend(new_path, executable_path);
		if (access(new_path, F_OK) == 0)
		{
			free(executable_path);
			executable_path = new_path;
			break ;
		}
		free(new_path);
		++it;
	}
	ft_strarr_del(paths);
	return (executable_path);
}

int	launch_executable(char **argv)
{
	extern t_shell_state	g_state;
	char **const			environment = htable_to_environ(g_state.envp);

	if (!environment || !argv)
	{
		ft_strarr_del(environment);
		return (1);
	}
	argv[0] = expand_executable_path(argv[0]);
	if (access(argv[0], F_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", argv[0]);
		ft_strarr_del(environment);
		return (127);
	}
	if (execve(argv[0], argv, environment) == -1)
	{
		perror(argv[0]);
		ft_strarr_del(environment);
		return (127);
	}
	ft_strarr_del(environment);
	return (1);
}
