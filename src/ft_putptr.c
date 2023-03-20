/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:53:22 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/09 10:47:16 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putptr_fd(int fd, void *ptr)
{
	unsigned long long	addr;
	int					res_a;
	int					res_b;

	addr = (unsigned long long)ptr;
	res_a = ft_write_str_fd(fd, "0x");
	if (res_a < 0)
		return (res_a);
	res_b = ft_puthex_lower_u64_fd(fd, addr);
	if (res_b < 0)
		return (res_a);
	return (res_a + res_b);
}

int	ft_putptr(void *ptr)
{
	return (ft_putptr_fd(STDOUT_FD, ptr));
}
