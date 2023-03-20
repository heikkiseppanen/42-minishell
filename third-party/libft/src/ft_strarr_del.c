/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:48:52 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/20 10:53:12 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strarr_del(char **arr)
{
	char	**it;

	if (!arr)
		return (NULL);
	it = arr;
	while (*it)
	{
		free(*it++);
	}
	free(arr);
	return (NULL);
}
