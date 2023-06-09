/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:19:25 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/09 11:06:20 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	put_cwd(char **argv)
{
	char	*buf;

	(void)argv;
	buf = malloc(1024);
	if (!buf)
		return (1);
	getcwd(buf, 1024);
	ft_printf("%s\n", buf);
	return (0);
}
