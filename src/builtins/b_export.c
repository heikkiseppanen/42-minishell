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

#include "include/ft/buf.h"
#include "libft.h"
#include "minishell.h"
#include "export.h"

static void	print_buf(t_buf *buf)
{
	size_t	b_iter;
	char	**memory;

	memory = (char **)buf->data;
	b_iter = 0;
	while (b_iter < buf->cap)
	{
		if (memory[b_iter])
			ft_printf("%s\n", memory[b_iter]);
		b_iter++;
	}
}

static int	put_exp(void)
{
	t_buf	*sorted_buf;
	char	**memory;
	size_t	i;

	sorted_buf = create_sorted_buf();
	if (!sorted_buf)
		return (1);
	print_buf(sorted_buf);
	memory = (char **)sorted_buf->data;
	i = 0;
	while (i < sorted_buf->cap)
	{
		if (memory[i])
			free(memory[i]);
		i++;
	}
	return ((size_t) buf_del_return(sorted_buf, NULL, FREE_A | BDEL_A, 1));
}

static void	destroy_splitarr(char **arr)
{
	if (!arr)
		return ;
	free(arr[0]);
	free(arr);
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
		destroy_splitarr(var_val);
	}
	return (0);
}
