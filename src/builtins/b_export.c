/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:09:17 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/05 16:06:02 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stddef.h>

static size_t	partition(const char **arr, size_t lo, size_t hi)
{
	const char		*pivot_value = arr[(hi - lo) / 2 + lo];
	const size_t	pivot_len = ft_strlen(pivot_value);
	const char		*tmp;

	while (1)
	{
		while (ft_strncmp(arr[lo], pivot_value, pivot_len) < 0)
			++lo;
		while (ft_strncmp(arr[hi], pivot_value, pivot_len) > 0)
			--hi;
		if (lo >= hi)
			return (hi);
		tmp = arr[hi];
		arr[hi] = arr[lo];
		arr[lo] = tmp;
	}
}

static void	str_qsort(const char **arr, size_t lo, size_t hi)
{
	size_t	pivot;

	if (lo >= hi)
		return ;
	pivot = partition(arr, lo, hi);
	str_qsort(arr, lo, pivot);
	str_qsort(arr, pivot + 1, hi);
}

static int	put_exp(void)
{
	extern t_shell_state	g_state;
	char					**environ;
	size_t					i;

	environ = htable_to_environ(g_state.envp);
	if (!environ)
		return (1);
	i = 0;
	while (environ[i])
		i++;
	str_qsort((const char **)environ, 0, i - 1);
	i = 0;
	while (environ[i])
	{
		ft_printf("declare -x %s\n", environ[i]);
		free(environ[i]);
		i++;
	}
	free(environ);
	return (0);
}

static int	assign_value(char **var_val, char **value)
{
	size_t	i;

	if (!var_val || !var_val[0])
		return (0);
	if (!var_val[1])
		*value = ft_strdup("");
	else
		*value = var_val[1];
	if (!(*value))
		return (0);
	if (ft_isdigit(var_val[0][0]))
		return (0);
	i = -1;
	while ((*var_val)[++i])
		if (!(ft_isalnum((*var_val)[i]) || (*var_val)[i] == '_'))
			return (0);
	return (1);
}

static char	**get_key_value(char *arg)
{
	char	**key_value;
	size_t	i;
	size_t	j;

	if (!arg || !ft_isalpha(*arg))
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '=')
			return (NULL);
		i++;
	}
	key_value = ft_calloc(sizeof(char **) * 3, 1);
	if (!key_value)
		return (NULL);
	key_value[2] = NULL;
	if (!arg[i])
	{
		key_value[0] = ft_strdup(arg);
		if (!key_value[0])
		{
			free(key_value);
			return (NULL);
		}
		return (key_value);
	}
	key_value[0] = ft_calloc(i + 1, 1);
	if (!key_value[0])
	{
		free(key_value);
		return (NULL);
	}
	i = -1;
	while (arg[++i] != '=')
		key_value[0][i] = arg[i];
	key_value[0][i] = '\0';
	if (!arg[i + 1])
		return (key_value);
	key_value[1] = ft_calloc(ft_strlen(arg) - i + 1, 1);
	if (!key_value[1])
	{
		free(key_value[0]);
		free(key_value);
		return (NULL);
	}
	j = 0;
	while (arg[++i])
	{
		key_value[1][j] = arg[i];
		j++;
	}
	key_value[1][j] = '\0';
	ft_printf("key: %s\tvalue: %s\n", key_value[0], key_value[1]);
	return (key_value);
}

int	export_var(char **argv)
{
	extern t_shell_state	g_state;
	char					**var_val;
	char					*value;
	size_t					cur_arg;

	cur_arg = 0;
	if (!argv[1])
		return (put_exp());
	while (argv[cur_arg++])
	{
		var_val = get_key_value(argv[cur_arg]);
		if (!assign_value(var_val, &value))
			return (1);
		if (!var_val[1] || ft_strchr(argv[cur_arg], '='))
			ft_htable_insert(g_state.envp, var_val[0], value);
		else
			ft_htable_insert(g_state.envp, var_val[0], NULL);
		free(var_val[0]);
		free(var_val);
	}
	return (0);
}
