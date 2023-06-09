/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:19:25 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/09 11:24:43 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	put_cwd(char **argv)
{
	char	buf[DIR_MAX];

	(void)argv;
	if (!getcwd(buf, DIR_MAX - 1))
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_printf("%s\n", buf);
	return (0);
}
