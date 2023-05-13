/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:20:19 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/13 04:20:43 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell_state	g_state; 

int	unset_var(char	**argv)
{
	(void)argv;
	ft_htable_remove(g_state.envp, argv[1]);
	return (0);
}
