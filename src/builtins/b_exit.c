/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:51:54 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/23 17:23:07 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stddef.h>

extern t_shell_state	g_state;

static int	count_args(char **argv)
{
	size_t		argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

int	exit_cmd(char **argv)
{
	const int	argc = count_args(argv);

	if (argc >= 2)
	{
		if (!ft_strncmp(argv[1], "0", 1) && ft_strlen(argv[1]) == 1)
			exit (0);
		g_state.pipeline_err = ft_atoi(argv[1]);
		if (!g_state.pipeline_err)
		{
			ft_fprintf(2, "exit\nminishell: exit: too many aruments\n");
			exit (255);
		}
		if (argc > 2)
		{
			ft_fprintf(2, "exit\nminishell: exit: numeric argument required\n");
			return (1);
		}
		exit (g_state.pipeline_err);
	}
	else
		exit(g_state.pipeline_err);
	return (0);
}
