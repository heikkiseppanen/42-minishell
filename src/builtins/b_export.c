/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:09:17 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/02 12:29:39 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft/buf.h"
#include "libft.h"
#include "minishell.h"
#include <stddef.h>

extern t_shell_state	g_state;

int	get_env_len(void)
{
	size_t	i;
	size_t	count;

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

char	get_smallest(t_buf *b, size_t index)
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

size_t	get_match_count(t_buf *b, size_t index, char smallest)
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

t_buf	*filter_cond(t_buf *b, size_t index, char smallest, size_t *pushed)
{
	t_buf		*filter_res;
	const char	**memory = (const char **)b->data;
	char		*cur_str;
	size_t		i;
	size_t		match_count;
	
	filter_res = malloc(sizeof(t_buf));
	match_count = get_match_count(b, index, smallest);
	if (!buf_init(filter_res, match_count, sizeof(char *)))
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
			{
				buf_del(b);
				free(b);
				return (NULL);
			}
			(*pushed)++;
		}
		i++;
	}
	buf_del(b);
	free(b);
	ft_printf("tfree: %p\n", b);
	return (filter_res);
}

t_buf	*remove_one_elem(t_buf *a, char *elem)
{
	size_t		memlen;
	size_t		elemlen;
	size_t		i;
	t_buf		*ret;
	const char	**memory = (const char **)a->data;

	ret = malloc(sizeof(t_buf));
	if (!buf_init(ret, a->cap - 1, sizeof(char *)))
	{
		free(ret);
		return (NULL);
	}
	i = 0;
	while (i < a->cap)
	{
		if (memory[i] && elem)
		{
			elemlen = ft_strlen(elem);
			memlen = ft_strlen(memory[i]);
			if (elemlen > memlen)
				elemlen = memlen;
			if ((ft_strncmp(memory[i], elem, elemlen)))
			{
				if (!buf_pushback(ret, &memory[i], 1))
				{
					buf_del(ret);
					free(ret);
					return (NULL);
				}
			}
		}
		i++;
	}
	buf_del(a);
	free(a);
	return (ret);
}

t_buf	*buf_copy(t_buf *a)
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
		{
			free(copy);
			buf_del(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

int	sort_bufs(t_buf *a, t_buf *b)
{
	t_buf	*t;
	size_t	i;
	size_t	pushed;
	char	smallest;
	char	**memory;

	while (a->cap >= 1)
	{
		i = 0;
		pushed = 0;
		t = buf_copy(a);
		ft_printf("tsort: %p\n", t);
		if (!t)
			return (0);
		memory = (char **)t->data;
		while (t->cap != 1)
		{
			smallest = get_smallest(t, i);
			t = filter_cond(t, i, smallest, &pushed);
			ft_printf("twhile: %p\n", t);
			if (!t)
				return (0);
			memory = (char **)t->data;
			i++;
		}
		if (a->cap != 1)
		{
			a = remove_one_elem(a, memory[0]);
			if (!a)
				return (0);
		}
		else
			a->cap = 0;
		if (!buf_pushback(b, &memory[0], 1))
		{
			buf_del(a);
			buf_del(t);
			free(a);
			free(t);
			return (0);
		}
		buf_del(t);
		free(t);
		ft_printf("tfree: %p\n", t);
	}
	buf_del(a);
	free(a);
	return (1);
}

t_buf	*create_sorted_buf()
{
	t_buf	*a;
	t_buf	b;
	t_buf	*sorted;
	char	**environ;
	int		len;

	a = malloc(sizeof(t_buf));
	if (!a)
		return (NULL);
	environ = htable_to_environ(g_state.envp);
	if (!environ)
		return (NULL);
	len = get_env_len();
	buf_init(a, len, sizeof(char *));
	buf_init(&b, len, sizeof(char *));
	if (!strarr_to_buf(environ, a))
	{
		buf_del(a);
		buf_del(&b);
		return (NULL);
	}
	if (!sort_bufs(a, &b))
	{
		buf_del(a);
		buf_del(&b);
		return (NULL);
	}
	sorted = buf_copy(&b);
	buf_del(&b);
	if (!sorted)
		return (NULL);
	free(environ);
	return (sorted);
}

void	print_buf(t_buf *buf)
{
	size_t	b_iter;
	char	**memory;

	b_iter = 0;
	while (b_iter < buf->cap)
	{
		memory = (char **)buf->data;
		if (memory[b_iter])
				ft_printf("%s\n", memory[b_iter]);
		b_iter++;
	}
}

int	put_exp(void)
{
	t_buf	*sorted_buf;
	char	**memory;
	size_t	i;

	sorted_buf = create_sorted_buf();
	if (!sorted_buf)
		return (1);
	print_buf(sorted_buf);
	memory = (char **)sorted_buf->data;
	i = 0;
	while (i < sorted_buf->cap)
	{
		if (memory[i])
			free(memory[i]);
		i++;
	}
	buf_del(sorted_buf);
	free(sorted_buf);
	return (0);
}

void	destroy_splitarr(char **arr)
{
	if (!arr)
		return ;
	free(arr[0]);
	free(arr);
}

int	export_var(char **argv)
{
	char	**var_val;
	char	*value;
	int		cur_arg;

	cur_arg = 0;
	if (!argv[1])
		return (put_exp());
	while (argv[cur_arg++])
	{
		var_val = ft_split(argv[cur_arg], '=');
		if (!var_val || !var_val[0])
			return (1);
		if (!var_val[1])
			value = ft_strdup("");
		else
			value = var_val[1];
		if (!value)
			return (1);
		if (!var_val[1] || ft_strchr(argv[cur_arg], '='))
			ft_htable_insert(g_state.envp, var_val[0], value);
		else
			ft_htable_insert(g_state.envp, var_val[0], NULL);
		destroy_splitarr(var_val);
	}
	return (0);
}
