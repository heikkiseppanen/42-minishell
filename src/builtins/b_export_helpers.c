/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:31:00 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/06 15:50:42 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

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

static void	print_variable(char *environ)
{
	size_t	i;

	ft_printf("declare -x ");
	i = 0;
	while (environ[i] != '=')
	{
		ft_printf("%c", environ[i]);
		i++;
	}
	if (!environ[i + 1])
	{
		ft_printf("\n");
		return ;
	}
	ft_printf("=\"");
	i++;
	while (environ[i])
	{
		ft_printf("%c", environ[i]);
		i++;
	}
	ft_printf("\"\n");
}

void	destroy_mult_value(void *one, void *two, void *three, void *four)
{
	if (one)
		free(one);
	else
		return ;
	if (two)
		free(two);
	if (three)
		free(three);
	if (four)
		free(four);
}

int	put_exp(void)
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
		print_variable(environ[i]);
		free(environ[i]);
		i++;
	}
	free(environ);
	return (0);
}
