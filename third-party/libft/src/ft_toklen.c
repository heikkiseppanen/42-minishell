/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toklen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:39:33 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/09 13:55:37 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_toklen(const char *str, char delim)
{
	const char	*it;

	it = str;
	while (*it && *it != delim)
		it++;
	return (it - str);
}
