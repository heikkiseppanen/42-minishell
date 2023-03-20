/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:29:08 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/09 10:46:41 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_upper_u64_fd(int fd, unsigned long long nb)
{
	return (ft_put_u64_base_fd(fd, nb, 16, "0123456789ABCDEF"));
}

int	ft_puthex_lower_u64_fd(int fd, unsigned long long nb)
{
	return (ft_put_u64_base_fd(fd, nb, 16, "0123456789abcdef"));
}

int	ft_puthex_upper_u64(unsigned long long nb)
{
	return (ft_puthex_upper_u64_fd(STDOUT_FD, nb));
}

int	ft_puthex_lower_u64(unsigned long long nb)
{
	return (ft_puthex_lower_u64_fd(STDOUT_FD, nb));
}
