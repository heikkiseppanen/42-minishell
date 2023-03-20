/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:54:16 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/20 10:15:46 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int n)
{
	char	*dup;

	dup = malloc((n + 1) * sizeof(*dup));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, str, n);
	dup[n] = '\0';
	return (dup);
}
