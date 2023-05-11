/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htable_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:54:37 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/11 20:58:16 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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

int	ft_htable_insert(t_htable *table, const char *key, void *value)
{
	char	*dup_key;
	int		rval;

	if (!key)
		return (-1);
	dup_key = ft_strdup(key);
	if (!table || !dup_key)
		return (-1);
	if (table->size == table->cap)
		rval = ft_restructure_table(table, dup_key, value);
	else
		rval = ft_probe_table(table, dup_key, value);
	return (rval);
}

void	*ft_htable_get(t_htable *table, const char *key)
{
	unsigned long long	key_hash;
	t_htelem			*orig_elem;

	if (!table || !key)
		return (NULL);
	key_hash = get_message_hash(key);
	orig_elem = table->memory[key_hash % table->cap];
	while (1)
	{
		if (table->memory[key_hash % table->cap])
		{
			if (!ft_strncmp(key, table->memory[key_hash % table->cap]->key, \
						ft_strlen(key)))
				return (table->memory[key_hash % table->cap]->value);
		}
		key_hash++;
		if (table->memory[key_hash % table->cap] == orig_elem)
			return (NULL);
	}
	return (NULL);
}

void	ft_htable_print(t_htable *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->cap)
	{
		if (table->memory[i])
			ft_printf("key: %s\tvalue: %s\tindex: %d\n", \
			table->memory[i]->key, (char *)table->memory[i]->value, i);
		i++;
	}
}

int	ft_htable_remove(t_htable *table, const char *key)
{
	unsigned long long	key_hash;
	t_htelem			*orig_elem;

	if (!table || !key)
		return (-1);
	key_hash = get_message_hash(key);
	orig_elem = table->memory[key_hash % table->cap];
	while (1)
	{
		if (table->memory[key_hash % table->cap])
		{
			if (!ft_strncmp(key, table->memory[key_hash % table->cap]->key, \
						ft_strlen(key)))
			{
				free((void *)table->memory[key_hash % table->cap]->key);
				free(table->memory[key_hash % table->cap]->value);
				free(table->memory[key_hash % table->cap]);
				table->memory[key_hash % table->cap] = NULL;
				return (0);
			}
		}
		key_hash++;
		if (table->memory[key_hash % table->cap] == orig_elem)
			return (-1);
	}
	return (-1);
}
