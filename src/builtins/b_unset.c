/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:20:19 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/23 17:24:42 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell_state	g_state;

int	unset_var(char	**argv)
{
  argv++;
	while (*argv)
	{
		ft_htable_remove(g_state.envp, *argv);
    argv++;
	}
	return (0);
}
