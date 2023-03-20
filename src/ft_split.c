/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:50:50 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/20 10:25:41 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	arr_size;
	size_t	tok_len;
	size_t	i;

	if (!s)
		return (NULL);
	arr_size = ft_strflds(s, c) + 1;
	arr = malloc(arr_size * sizeof(*arr));
	if (!arr)
		return (NULL);
	arr[arr_size - 1] = NULL;
	i = 0;
	while (i < arr_size - 1)
	{
		while (*s == c)
			s++;
		tok_len = ft_toklen(s, c);
		arr[i] = ft_strndup(s, tok_len);
		if (!arr[i])
			return (ft_strarr_del(arr));
		s += tok_len;
		i++;
	}
	return (arr);
}
