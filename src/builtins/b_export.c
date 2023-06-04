/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:09:17 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/02 17:58:51 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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
		ft_printf("%s\n", environ[i]);
		free(environ[i]);
		i++;
	}
	free(environ);
	return (0);
}

static int	assign_value(char **var_val, char **value)
{
	if (!var_val || !var_val[0])
		return (0);
	if (!var_val[1])
		*value = ft_strdup("");
	else
		*value = var_val[1];
	if (!(*value))
		return (0);
	return (1);
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
		var_val = ft_split(argv[cur_arg], '=');
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
