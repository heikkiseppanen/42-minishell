/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:17:56 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/02 17:24:48 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"
#include "minishell.h"

static char	get_smallest_char(t_buf *b, size_t index)
{
	const char	**memory = (const char **)b->data;
	char		*cur_str;
	size_t		i;
	char		smallest;

	smallest = 127;
	i = 0;
	while (i < b->cap)
	{
		cur_str = (char *)memory[i];
		if (!cur_str)
			return (0);
		if (ft_strlen(cur_str) < index + 2)
		{
			i++;
			continue ;
		}
		if (cur_str[index] < smallest)
			smallest = cur_str[index];
		i++;
	}
	return (smallest);
}

static t_buf	*buf_copy(t_buf *a)
{
	const char	**memory = (const char **)a->data;
	t_buf		*copy;
	size_t		i;

	copy = malloc(sizeof(t_buf));
	if (!copy)
		return (NULL);
	buf_init(copy, a->cap, sizeof(char *));
	i = 0;
	while (i < a->cap)
	{
		if (!memory[i])
		{
			i++;
			continue ;
		}
		if (!buf_pushback(copy, &memory[i], 1))
			return (buf_del_return(copy, NULL, FREE_A | BDEL_A, 0));
		i++;
	}
	return (copy);
}

char	*get_smallest_string(t_buf *a)
{
	char	*smallest_string;
	char	smallest_char;
	t_buf	*t;
	size_t	i;

	t = buf_copy(a);
	if (!t)
		return (0);
	i = 0;
	while (t->cap != 1)
	{
		smallest_char = get_smallest_char(t, i);
		t = filter_cond(t, i, smallest_char);
		if (!t)
			return (NULL);
		i++;
	}
	smallest_string = ((char **)t->data)[0];
	return (buf_del_return(t, NULL, BDEL_A | FREE_A, (size_t)smallest_string));
}

int	sort_bufs(t_buf *a, t_buf *b)
{
	char	*smallest_string;

	while (a->cap >= 1LL)
	{
		smallest_string = get_smallest_string(a);
		if (a->cap != 1)
		{
			a = remove_one_elem(a, smallest_string);
			if (!a)
				return (0);
		}
		else
			a->cap = 0;
		if (!buf_pushback(b, &smallest_string, 1))
			return ((size_t)buf_del_return(a, NULL, FREE_A | BDEL_A, 0));
	}
	return ((size_t)buf_del_return(a, NULL, FREE_A | BDEL_A, 1));
}

t_buf	*create_sorted_buf(void)
{
	extern t_shell_state	g_state;
	t_buf					*a;
	t_buf					b;
	t_buf					*sorted;
	char					**environ;

	a = malloc(sizeof(t_buf));
	environ = htable_to_environ(g_state.envp);
	if (!a || !environ || !init_bufs(a, &b))
		return (buf_del_return((t_buf *)environ, NULL, FREE_A, 0));
	if (!strarr_to_buf(environ, a))
		return (buf_del_return(a, &b, FREE_A | BDEL_A | BDEL_B, 0));
	if (!sort_bufs(a, &b))
		return (buf_del_return(a, &b, FREE_A | BDEL_A | BDEL_B, 0));
	sorted = buf_copy(&b);
	if (!sorted)
		return (buf_del_return(&b, NULL, BDEL_A, 0));
	return (buf_del_return((t_buf *)environ, &b, FREE_A
			| BDEL_B, (size_t)sorted));
}
