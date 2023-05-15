/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:09:17 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/13 05:30:29 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell_state	g_state;

int	put_exp(char	**argv)
{
	size_t					i;

	(void)argv;
	i = 0;
	while (i < g_state.envp->cap)
	{
		if (g_state.envp->memory[i])
			ft_printf("%s=%s\n", g_state.envp->memory[i]->key,
				g_state.envp->memory[i]->value);
		i++;
	}
	return (0);
}

int	export_var(char **argv)
{
	char					**var_val;
	char					*value;
	int						cur_arg;

	cur_arg = 1;
	if (!argv[cur_arg])
		put_exp(argv);
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
		ft_htable_insert(g_state.envp, var_val[0], value);
		cur_arg++;
	}
	return (0);
}
