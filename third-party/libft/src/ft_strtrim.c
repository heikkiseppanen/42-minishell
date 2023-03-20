/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:15:22 by hseppane          #+#    #+#             */
/*   Updated: 2022/11/02 21:33:20 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*rhs;
	char		*str;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	rhs = s1 + len - 1;
	while ((s1 < rhs) && ft_strchr(set, *s1))
	{
		s1++;
		len--;
	}
	while ((rhs >= s1) && ft_strchr(set, *rhs))
	{
		rhs--;
		len--;
	}
	str = malloc((len + 1) * sizeof(*str));
	if (!str)
		return (str);
	ft_memcpy(str, s1, len * sizeof(*rhs));
	str[len] = '\0';
	return (str);
}
