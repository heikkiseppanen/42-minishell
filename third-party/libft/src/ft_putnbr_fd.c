/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:09:07 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/01 15:09:20 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	buf[12];
	char	*it;
	int		sign;
	int		total_write;

	it = buf;
	sign = (n < 0);
	total_write = 0;
	if (n == 0)
		*it++ = '0';
	if (sign)
	{
		*it++ = -(char)(n % 10) + '0';
		n /= -10;
	}
	while (n)
	{
		*it++ = (char)(n % 10) + '0';
		n /= 10;
	}
	if (sign)
		*it++ = '-';
	while (it-- != buf)
		total_write += ft_putchar_fd(*it, fd);
	return (total_write);
}
