/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:09:17 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/17 08:14:32 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

extern t_shell_state	g_state;

int	put_exp(void)
{
	size_t	i;
	char	*key;
	char	*value;

	i = 0;
	while (i < g_state.envp->cap)
	{
		if (g_state.envp->memory[i])
		{
			value = (char *)g_state.envp->memory[i]->value;
			key = (char *)g_state.envp->memory[i]->key;
			if (!(value))
				ft_printf("%s\n", key);
			else
				ft_printf("%s=\"%s\"\n", key, value);
		}
		i++;
	}
	return (0);
}

void	destroy_splitarr(char **arr)
{
	if (!arr)
		return ;
	free(arr[0]);
	free(arr);
}

int	export_var(char **argv)
{
	char	**var_val;
	char	*value;
	int		cur_arg;

	cur_arg = 1;
	if (!argv[cur_arg])
		put_exp();
	while (argv[cur_arg])
	{
		var_val = ft_split(argv[cur_arg], '=');
		if (!var_val || !var_val[0])
			return (1);
		if (!var_val[1])
			value = ft_strdup("");
		else
			value = var_val[1];
		if (!value)
			return (1);
		if (var_val[1] || ft_strchr(argv[cur_arg], '='))
			ft_htable_insert(g_state.envp, var_val[0], value);
		else
			ft_htable_insert(g_state.envp, var_val[0], NULL);
		cur_arg++;
		destroy_splitarr(var_val);
	}
	return (0);
}
