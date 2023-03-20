/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:11:25 by hseppane          #+#    #+#             */
/*   Updated: 2022/11/02 21:33:20 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*it1;
	const unsigned char	*it2;

	if (n == 0)
		return (0);
	it1 = (const unsigned char *)s1;
	it2 = (const unsigned char *)s2;
	while (n--)
	{
		if (*it1 != *it2)
			return (*it1 - *it2);
		it1++;
		it2++;
	}
	return (0);
}
