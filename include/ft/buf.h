/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:15:17 by hseppane          #+#    #+#             */
/*   Updated: 2023/03/20 09:17:06 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNARR_H
# define DYNARR_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_buf
{
	void	*data;
	size_t	stride;
	size_t	size;
	size_t	cap;
}			t_buf;

int		buf_init(t_buf *arr, size_t size, size_t type_size);
void	buf_del(t_buf *arr);
int		buf_resize(t_buf *arr, size_t new_cap);
int		buf_pushback(t_buf *arr, void *type_data, size_t count);
ssize_t	buf_read(t_buf *arr, int fd, size_t bytes);

#endif
