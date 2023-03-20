/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:27:13 by hseppane          #+#    #+#             */
/*   Updated: 2022/11/02 21:28:20 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intdigits(int n)
{
	int	digits;

	digits = 0;
	if (!n)
		return (1);
	while (n)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

static char	*ft_strrev(char *str)
{
	char	*lhs;
	char	*rhs;
	char	tmp;

	if (!*str)
		return (str);
	lhs = str;
	rhs = str;
	while (*rhs)
		rhs++;
	rhs--;
	while (lhs < rhs)
	{
		tmp = *lhs;
		*lhs = *rhs;
		*rhs = tmp;
		lhs++;
		rhs--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	char	*it;
	int		sign;

	sign = (n < 0);
	str = malloc((ft_intdigits(n) + sign + 1) * sizeof(*str));
	if (!str)
		return (NULL);
	it = str;
	if (!n)
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
	*it = '\0';
	return (ft_strrev(str));
}
