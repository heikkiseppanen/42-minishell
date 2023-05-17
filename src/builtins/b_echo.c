/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:13:09 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/17 07:25:30 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft/buf.h"
#include "libft.h"

int	parse_echostr(char **argv, t_buf *buf, int *nline_flag)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], "-n", 2) && i == 1 && ft_strlen(argv[i]) == 2)
		{
			*nline_flag = 1;
			i++;
			continue ;
		}
		if (!buf_pushback(buf, argv[i], ft_strlen(argv[i])))
			return (0);
		if (argv[i + 1])
		{
			if (!buf_pushback(buf, " ", 1))
				return (0);
		}
		i++;
	}
	if (!buf_pushback(buf, "", 1))
		return (0);
	return (1);
}

int	echo(char **argv)
{
	int		nline_flag;
	t_buf	buf;

	nline_flag = 0;
	if (!buf_init(&buf, 1024, 1))
		return (1);
	if (!parse_echostr(argv, &buf, &nline_flag))
	{
		buf_del(&buf);
		return (1);
	}
	if (nline_flag)
		ft_printf("%s", buf.data);
	else
		ft_printf("%s\n", buf.data);
	buf_del(&buf);
	return (0);
}
