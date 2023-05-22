/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:51:54 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/22 16:09:50 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

extern t_shell_state	g_state;

int	exit_cmd(char	**argv)
{
	const char *err_argmax = "exit\nminishell: exit: too many arguments\n";
	const char *err_argnum = "exit\nminishell: exit: numeric argument required\n";
	size_t		exit_status;
	size_t	argc;

	argc = 0;
	exit_status = 0;
	while (argv[argc])
		argc++;
	if (argc >= 2)
	{
		if (!ft_strncmp(argv[1], "0", 1) && ft_strlen(argv[1]) == 1)
			exit (0);
		exit_status = ft_atoi(argv[1]);
		if (!exit_status)
		{
			write(2, err_argnum, ft_strlen(err_argnum));
			exit (255);
		}
		if (argc > 2)
		{
			write(2, err_argmax, ft_strlen(err_argmax));
			return (1);
		}
		exit (exit_status);
	}
	else
		exit(g_state.pipeline_err);
	return (0);
}
