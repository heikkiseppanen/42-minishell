/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:29:08 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/01 15:06:17 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_upper_u64_fd(unsigned long long nb, int fd)
{
	return (ft_put_u64_base_fd(nb, 16, "0123456789ABCDEF", fd));
}

int	ft_puthex_lower_u64_fd(unsigned long long nb, int fd)
{
	return (ft_put_u64_base_fd(nb, 16, "0123456789abcdef", fd));
}

int	ft_puthex_upper_u64(unsigned long long nb)
{
	return (ft_puthex_upper_u64_fd(nb, STDOUT_FILENO));
}

int	ft_puthex_lower_u64(unsigned long long nb)
{
	return (ft_puthex_lower_u64_fd(nb, STDOUT_FILENO));
}
