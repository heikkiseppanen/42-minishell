/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:19:55 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/02 17:20:26 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	*buf_del_return(t_buf *a, t_buf *b,
		unsigned char free_flags, size_t rval)
{
	if (free_flags & BDEL_A)
		buf_del(a);
	if (free_flags & BDEL_B)
		buf_del(b);
	if (free_flags & FREE_A)
		free(a);
	if (free_flags & FREE_B)
		free(b);
	return ((void *)rval);
}

int	strarr_to_buf(char **arr, t_buf *buf)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
	{
		if (!buf_pushback(buf, &arr[i], 1))
			return (0);
		i++;
	}
	return (1);
}

t_buf	*filter_cond(t_buf *b, size_t index, char smallest)
{
	t_buf		*filter_res;
	const char	**memory = (const char **)b->data;
	char		*cur_str;
	size_t		i;

	if (!init_filter_res(&filter_res, b, index, smallest))
		return (NULL);
	i = 0;
	while (i < b->cap)
	{
		cur_str = (char *)memory[i];
		if (ft_strlen(cur_str) < index + 2)
		{
			i++;
			continue ;
		}
		if (cur_str[index] == smallest)
		{
			if (!buf_pushback(filter_res, &cur_str, 1))
				return (buf_del_return(b, filter_res, FREE_A | FREE_B
						| BDEL_A | BDEL_B, 0));
		}
		i++;
	}
	return (buf_del_return(b, NULL, 1 | 4, (size_t)filter_res));
}

t_buf	*remove_one_elem(t_buf *a, char *elem)
{
	size_t		elemlen;
	size_t		i;
	t_buf		*ret;
	const char	**memory = (const char **)a->data;

	ret = init_remove_res(a);
	i = 0;
	while (i < a->cap)
	{
		if (memory[i] && elem)
		{
			elemlen = ft_strlen(elem);
			if (elemlen > ft_strlen(memory[i]))
				elemlen = ft_strlen(memory[i]);
			if ((ft_strncmp(memory[i], elem, elemlen)))
			{
				if (!buf_pushback(ret, &memory[i], 1))
					return (buf_del_return(ret, NULL, FREE_A | BDEL_A, 0));
			}
		}
		i++;
	}
	return (buf_del_return(a, NULL, FREE_A | BDEL_A, (size_t)ret));
}
