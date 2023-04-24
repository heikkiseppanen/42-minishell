/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 07:37:09 by lsileoni          #+#    #+#             */
/*   Updated: 2023/04/24 17:13:38 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#define FNV_PRIME 0x100000001b3
#define FNV_OFFSET 0xcbf29ce484222325

typedef struct s_htelem
{
	const char	*key;
	void		*value;
}	t_htelem;

typedef struct s_htable
{
	t_htelem	**memory;
	size_t		size;
	size_t		cap;
}	t_htable;

int	ft_htable_insert(t_htable *table, const char *key, void *value);

long long	get_message_hash(const char *message)
{
	long long	hash;

	if (!message)
		return (0);
	hash = FNV_OFFSET;
	while (*message)
	{
		hash = hash ^ *message;
		hash = hash * FNV_PRIME;
		message++;
	}
	return (hash);
}

t_htable	*ft_htable_create(unsigned int init_size)
{
	t_htable	*rtable;

	rtable = ft_calloc(sizeof(t_htable), 1);
	if (!rtable || (init_size % 2) || (init_size == 0))
		return (NULL);
	rtable->memory = ft_calloc(sizeof(t_htelem **), init_size);
	if (!rtable->memory)
	{
		free(rtable);
		return (NULL);
	}
	rtable->cap = init_size;
	return (rtable);
}

int	ft_restructure_table(t_htable *table, const char *key, void *value)
{
	t_htable	*tmp;
	int			i;

	tmp = ft_htable_create(table->cap * 2);
	if (!tmp)
		return (-1);
	i = 0;
	while (i < table->cap)
	{
		ft_htable_insert(tmp, table->memory[i]->key, table->memory[i]->value);
		free(table->memory[i]);
		i++;
	}
	ft_htable_insert(tmp, key, value);
	free(table->memory);
	table->memory = tmp->memory;
	free(tmp);
	table->cap *= 2;
	table->size++;
	return (1);
}

int	ft_probe_table(t_htable *table, const char *key, void *value)
{
	unsigned long long	key_hash;

	key_hash = get_message_hash(key);
	while (1)
	{
		if (!table->memory[key_hash % table->cap])
		{
			table->memory[key_hash % table->cap] = malloc(sizeof(t_htelem));
			table->memory[key_hash % table->cap]->key = key;
			table->memory[key_hash % table->cap]->value = value;
			table->size++;
			break ;
		}
		else if (!ft_strncmp(key, table->memory[key_hash % table->cap]->key, \
					ft_strlen(key)))
		{
			free(table->memory[key_hash % table->cap]->value);
			table->memory[key_hash % table->cap]->value = value;
			break ;
		}
		key_hash++;
	}
	return (0);
}

int	ft_htable_insert(t_htable *table, const char *key, void *value)
{
	if (!table || !key)
		return (-1);
	if (table->size == table->cap)
		return (ft_restructure_table(table, key, value));
	return (ft_probe_table(table, key, value));
}

void	*ft_htable_get(t_htable *table, const char *key)
{
	unsigned long long	key_hash;
	void				*content;
	t_htelem			*orig_elem;

	if (!table || !key)
		return (NULL);
	key_hash = get_message_hash(key);
	orig_elem = table->memory[key_hash % table->cap];
	while (1)
	{
		if (!ft_strncmp(key, table->memory[key_hash % table->cap]->key, \
					ft_strlen(key)))
			return (table->memory[key_hash % table->cap]->value);
		key_hash++;
		if (table->memory[key_hash % table->cap] == orig_elem)
			return (NULL);
	}
	return (NULL);
}

void	ft_print_htable(t_htable *table)
{
	int	i;

	i = 0;
	while (i < table->cap)
	{
		if (table->memory[i])
			ft_printf("key: %s\tvalue: %s\tindex: %d\n", \
			table->memory[i]->key, (char *)table->memory[i]->value, i);
		i++;
	}
}
