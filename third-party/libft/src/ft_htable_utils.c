/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 07:37:09 by lsileoni          #+#    #+#             */
/*   Updated: 2023/04/26 14:00:34 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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

int	ft_restructure_table(t_htable *table, const char *key, void *value)
{
	t_htable	*tmp;
	unsigned int			i;

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
