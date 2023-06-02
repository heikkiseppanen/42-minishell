/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:06:03 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/02 17:41:49 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H
# include "libft.h"

enum e_free_flags
{
	FREE_A = 1,
	FREE_B = 2,
	BDEL_A = 4,
	BDEL_B = 8,
};

void	*buf_del_return(t_buf *a, t_buf *b,
			unsigned char free_flags, size_t rval);
int		init_bufs(t_buf *a, t_buf *b);
t_buf	*init_filter_res(t_buf **filter_res, t_buf *b,
			size_t index, char smallest);
t_buf	*init_remove_res(t_buf *a);
int		strarr_to_buf(char **arr, t_buf *buf);
t_buf	*filter_cond(t_buf *b, size_t index, char smallest);
t_buf	*remove_one_elem(t_buf *a, char *elem);
t_buf	*create_sorted_buf(void);

#endif
