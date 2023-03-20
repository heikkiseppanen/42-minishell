/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:29:52 by hseppane          #+#    #+#             */
/*   Updated: 2023/03/20 09:34:06 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	nb;
	int		sign;

	nb = 0;
	sign = 1;
	while (ft_isspace(*str))
	{
		str++;
	}
	if (!ft_isdigit(*str))
	{
		if (*str == '-')
			sign = -1;
		else if (*str != '+')
			return (nb);
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	return (nb * sign);
}
