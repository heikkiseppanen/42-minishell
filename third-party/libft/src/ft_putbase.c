/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:17:27 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/01 15:05:44 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	u64_base_digits(unsigned long long nb, int base)
{
	int	digits;

	digits = 0;
	if (!nb)
		return (1);
	while (nb)
	{
		digits++;
		nb /= base;
	}
	return (digits);
}

int	ft_put_u64_base_fd(unsigned long long nb, int base, char *set, int fd)
{
	const int	digits = u64_base_digits(nb, base);
	char		out[sizeof(nb) * 8];
	char		*it;

	if (base <= 1)
		return (0);
	it = out + digits - 1;
	if (!nb)
		*it-- = '0';
	else
	{
		while (nb)
		{
			*it-- = set[nb % base];
			nb /= base;
		}
	}
	return (write(fd, out, digits));
}

int	ft_put_i64_base_fd(long long nb, int base, char *set, int fd)
{
	int	bytes;

	if (nb < 0)
	{
		bytes = ft_putchar_fd('-', fd);
		if (bytes < 0)
			return (bytes);
		bytes += ft_put_u64_base_fd(-(unsigned long long)nb, base, set, fd);
		return (bytes);
	}
	return (ft_put_u64_base_fd((unsigned long long)nb, base, set, fd));
}
