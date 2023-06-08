/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:40:36 by hseppane          #+#    #+#             */
/*   Updated: 2023/06/05 11:31:24 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

t_shell_state	g_state;

static int	increment_shlvl(void)
{
	char			*level;
	char			*tmp;
	int				shlvl;

	tmp = ft_htable_get(g_state.envp, "SHLVL");
	if (!tmp)
	{
		level = ft_itoa(1);
		if (!level)
			return (0);
		if (ft_htable_insert(g_state.envp, "SHLVL", level) == -1)
			return (0);
		return (1);
	}
	shlvl = ft_atoi(tmp);
	if (ft_htable_remove(g_state.envp, "SHLVL") == -1)
		return (0);
	level = ft_itoa(shlvl + 1);
	if (!level)
		return (0);
	if (ft_htable_insert(g_state.envp, "SHLVL", level) == -1)
		return (0);
	return (1);
}

static t_err	init_envp(void)
{
	extern char		**environ;
	unsigned int	i;
	char			*key;
	char			*value;

	g_state.envp = ft_htable_create(128);
	while (*environ)
	{
		i = 0;
		while ((*environ)[i] != '=' && (*environ)[i])
			i++;
		key = ft_strndup(*environ, i);
		++i;
		value = ft_strndup(*environ + i, ft_strlen(*environ + i));
		ft_htable_insert(g_state.envp, key, value);
		free(key);
		++environ;
	}
	return (MS_SUCCESS);
}

static int	assign_value_to_htable(t_htable *envp, char **env,
									 unsigned int i, unsigned int j)
{
	char			*tmp;

	tmp = ft_strjoin(envp->memory[i]->key, "=");
	if (!tmp)
	{
		ft_strarr_del(env);
		return (0);
	}
	env[j] = ft_strjoin(tmp, envp->memory[i]->value);
	if (!env[j])
	{
		free(tmp);
		ft_strarr_del(env);
		return (0);
	}
	free(tmp);
	return (1);
}

char	**htable_to_environ(t_htable *envp)
{
	char			**env;
	unsigned int	i;
	unsigned int	j;

	env = malloc(sizeof(char *) * (envp->size + 1));
	if (!env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < envp->cap)
	{
		if (envp->memory[i])
		{
			if (!assign_value_to_htable(envp, env, i, j))
				return (NULL);
			j++;
		}
		i++;
	}
	env[j] = NULL;
	return (env);
}

t_err	ms_init(void)
{
	g_state = (t_shell_state){};
	if (!init_envp() || !increment_shlvl())
	{
		perror("Failed to init shell.");
		return (MS_FAIL);
	}
	return (MS_SUCCESS);
}
