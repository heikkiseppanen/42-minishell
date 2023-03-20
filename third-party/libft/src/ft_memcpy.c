/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:19:00 by hseppane          #+#    #+#             */
/*   Updated: 2022/11/02 21:33:20 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	chunks;
	void	*dp;

	if ((dst == src) || (!dst && !src) || n == 0)
		return (dst);
	dp = dst;
	chunks = n / sizeof(unsigned long);
	n -= chunks * sizeof(unsigned long);
	while (chunks--)
	{
		*(unsigned long *)dp = *(const unsigned long *)src;
		dp = (unsigned long *)dp + 1;
		src = (const unsigned long *)src + 1;
	}
	while (n--)
	{
		*(unsigned char *)dp = *(const unsigned char *)src;
		dp = (unsigned char *)dp + 1;
		src = (const unsigned char *)src + 1;
	}
	return (dst);
}
