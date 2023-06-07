/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:26:40 by hseppane          #+#    #+#             */
/*   Updated: 2023/06/05 11:38:07 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTABLE_H
# define HTABLE_H

# include <stdlib.h>

# define FNV_PRIME 0x100000001b3
# define FNV_OFFSET 0xcbf29ce484222325

typedef struct s_htelem
{
	const char	*key;
	void		*value;
}	t_htelem;

typedef struct s_hmap
{
	t_htelem	**memory;
	size_t		size;
	size_t		cap;
}	t_htable;

t_htable	*ft_htable_create(unsigned int init_size);

long long	get_message_hash(const char *message);
int			ft_htable_insert(t_htable *table, const char *key, void *value);
int			ft_restructure_table(t_htable *table, const char *key, void *value);
int			ft_probe_table(t_htable *table, const char *key, void *value);
int			ft_htable_insert(t_htable *table, const char *key, void *value);
void		*ft_htable_get(t_htable *table, const char *key);
void		ft_htable_print(t_htable *table);
int			ft_htable_remove(t_htable *table, const char *key);
void		ft_htable_destroy(t_htable *table, unsigned char destroy_value);
int			remove_htable_elem(t_htable *table, unsigned long long key_hash);

#endif
