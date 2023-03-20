/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:10:38 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/09 10:37:36 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynarr.h"

#include "libft.h"

void	*dynarr_init(t_dynarr *arr, size_t size, size_t type_size)
{
	unsigned char	*it;

	if (!arr)
		return (NULL);
	if (arr->ptr)
		dynarr_del(arr);
	arr->ptr = malloc(size * type_size);
	if (arr->ptr)
	{
		arr->type_size = type_size;
		arr->cap = size;
		it = (unsigned char *)arr->ptr;
		ft_bzero(arr->ptr, arr-> size * arr->type_size);
	}
	else
		arr->cap = 0;
	arr->size = 0;
	return (arr->ptr);
}

void	dynarr_del(t_dynarr *arr)
{
	if (arr->ptr)
		free(arr->ptr);
	arr->ptr = NULL;
	arr->type_size = 0;
	arr->size = 0;
	arr->cap = 0;
}

void	*dynarr_resize(t_dynarr *arr, size_t new_cap)
{
	unsigned char	*tmp;

	if (!arr || !arr->ptr)
		return (NULL);
	if (new_cap == arr->cap)
		return (arr->ptr);
	tmp = malloc(new_cap * arr->type_size);
	if (!tmp)
		return (NULL);
	if (new_cap < arr->size)
	{
		ft_memcpy(tmp, arr->ptr, new_cap * arr->type_size);
		arr->size = new_cap;
	}
	else
		ft_memcpy(tmp, arr->ptr, arr->size * arr->type_size);
	free(arr->ptr);
	arr->ptr = tmp;
	arr->cap = new_cap;
	return (arr->ptr);
}

ssize_t	dynarr_read(t_dynarr *arr, int fd, size_t bytes)
{
	size_t			byte_cap;
	size_t			byte_size;
	ssize_t			read_size;
	void			*dst;

	byte_size = arr->size * arr->type_size;
	byte_cap = arr->cap * arr->type_size;
	if (byte_size + bytes > byte_cap)
	{
		if (dynarr_resize(arr, 2 * arr->cap))
		{
			byte_size = arr->size * arr->type_size;
			byte_cap = arr->cap * arr->type_size;
		}
		else
			return (-1);
	}
	dst = (unsigned char *)arr->ptr + byte_size;
	read_size = read(fd, dst, bytes);
	if (read_size > 0)
		arr->size += read_size;
	return (read_size);
}
