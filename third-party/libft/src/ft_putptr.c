/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:53:22 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/01 15:23:41 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putptr_fd(void *ptr, int fd)
{
	unsigned long long	addr;
	int					res_a;
	int					res_b;

	addr = (unsigned long long)ptr;
	if (!addr)
		return (ft_putstr_fd("(null)", fd));
	res_a = ft_putstr_fd("0x", fd);
	if (res_a < 2)
		return (res_a);
	res_b = ft_puthex_lower_u64_fd(addr, fd);
	if (res_b < 0)
		return (res_a);
	return (res_a + res_b);
}

int	ft_putptr(void *ptr)
{
	return (ft_putptr_fd(ptr, STDOUT_FILENO));
}
