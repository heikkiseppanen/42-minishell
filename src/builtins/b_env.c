/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:18:19 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/13 04:18:45 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell_state	g_state;

int	put_env(char	**argv)
{
	size_t					i;

	(void)argv;
	i = 0;
	while (i < g_state.envp->cap)
	{
		if (g_state.envp->memory[i])
			ft_printf("%s=%s\n", g_state.envp->memory[i]->key, g_state.envp->memory[i]->value);
		i++;
	}
	return (0);
}
