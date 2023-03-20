/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:32:19 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/09 10:46:59 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putdec_u64_fd(int fd, unsigned long long nb)
{
	return (ft_put_u64_base_fd(fd, nb, 10, "0123456789"));
}

int	ft_putdec_i64_fd(int fd, long long nb)
{
	return (ft_put_i64_base_fd(fd, nb, 10, "0123456789"));
}

int	ft_putdec_u64(unsigned long long nb)
{
	return (ft_putdec_u64_fd(STDOUT_FD, nb));
}

int	ft_putdec_i64(long long nb)
{
	return (ft_putdec_i64_fd(STDOUT_FD, nb));
}
