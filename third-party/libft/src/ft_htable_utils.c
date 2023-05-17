/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 07:37:09 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/17 08:07:24 by lsileoni         ###   ########.fr       */
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
	t_htable			*tmp;
	unsigned int		i;

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
	unsigned long long	index;
	char				*dup_key;

	key_hash = get_message_hash(key);
	while (1)
	{
		index = key_hash % table->cap;
		if (!table->memory[index])
		{
			dup_key = ft_strdup(key);
			if (!dup_key)
				return (-1);
			table->memory[index] = malloc(sizeof(t_htelem));
			table->memory[index]->key = dup_key;
			table->memory[index]->value = value;
			table->size++;
			break ;
		}
		else if (!ft_strncmp(key, table->memory[index]->key, \
					ft_strlen(key)))
		{
			if (table->memory[index]->value)
				free(table->memory[index]->value);
			table->memory[index]->value = value;
			break ;
		}
		key_hash++;
	}
	return (1);
}
