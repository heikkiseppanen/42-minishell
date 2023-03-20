/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 09:14:49 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/12 10:48:55 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>

int	ft_write_str_fd(int fd, const char *str)
{
	size_t	len;

	if (!str)
		return (ft_write_str_fd(fd, "(null)"));
	len = ft_strlen(str);
	return (write(fd, str, len));
}

int	ft_write_str(const char *str)
{
	return (ft_write_str_fd(STDOUT_FD, str));
}
