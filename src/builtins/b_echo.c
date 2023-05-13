/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:13:09 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/13 04:13:29 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	echo(char **argv)
{
	char	*echo_str;
	int		nline_flag;
	int		i;

	i = 1;
	nline_flag = 0;
	echo_str = "";
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], "-n", 2) && i == 1)
		{
			nline_flag = 1;
			i++;
			continue ;
		}
		echo_str = ft_strjoin(echo_str, argv[i]);
		if (!echo_str)
			return (1);
		if (argv[i + 1])
			echo_str = ft_strjoin(echo_str, " " );
		if (!echo_str)
			return (1);
		i++;
	}
	if (nline_flag)
		ft_printf("%s", echo_str);
	else
		ft_printf("%s\n", echo_str);
	return (0);
}
