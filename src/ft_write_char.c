/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:05:22 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/12 10:49:46 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>

int	ft_write_char_fd(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_write_char(char c)
{
	return (ft_write_char_fd(STDOUT_FD, c));
}
