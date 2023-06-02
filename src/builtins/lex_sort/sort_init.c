/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:12:54 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/02 17:28:07 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"
#include "minishell.h"

static int	get_env_len(void)
{
	extern t_shell_state	g_state;
	size_t					i;
	size_t					count;

	count = 0;
	i = 0;
	while (i < g_state.envp->cap)
	{
		if (g_state.envp->memory[i])
			count++;
		i++;
	}
	return (count);
}

static size_t	get_match_count(t_buf *b, size_t index, char smallest)
{
	const char	**memory = (const char **)b->data;
	char		*cur_str;
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (i < b->cap)
	{
		cur_str = (char *)memory[i];
		if (ft_strlen(cur_str) < index + 2)
		{
			i++;
			continue ;
		}
		if (cur_str[index] == smallest)
			count++;
		i++;
	}
	return (count);
}

int	init_bufs(t_buf *a, t_buf *b)
{
	int	len;

	len = get_env_len();
	if (!buf_init(a, len, sizeof(char *)))
		return ((size_t) buf_del_return(a, NULL, FREE_A, 0));
	if (!buf_init(b, len, sizeof(char *)))
		return ((size_t) buf_del_return(a, NULL, FREE_A | BDEL_A, 0));
	return (1);
}

t_buf	*init_filter_res(t_buf **filter_res, t_buf *b,
		size_t index, char smallest)
{
	size_t	match_count;

	*filter_res = malloc(sizeof(t_buf));
	if (!filter_res)
		return (buf_del_return(b, NULL, FREE_A | BDEL_A, 0));
	match_count = get_match_count(b, index, smallest);
	if (!buf_init(*filter_res, match_count, sizeof(char *)))
		return (buf_del_return(b, NULL, FREE_A | BDEL_A, 0));
	return (*filter_res);
}

t_buf	*init_remove_res(t_buf *a)
{
	t_buf	*ret;

	ret = malloc(sizeof(t_buf));
	if (!ret)
		return (buf_del_return(a, NULL, FREE_A | BDEL_A, 0));
	if (!buf_init(ret, a->cap - 1, sizeof(char *)))
		return (buf_del_return(ret, NULL, FREE_A, 0));
	return (ret);
}
