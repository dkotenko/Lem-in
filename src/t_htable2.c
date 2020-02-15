/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_htable2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:47:48 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 14:33:59 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_htable		*t_htable_resize(t_htable *table)
{
	t_htable	*new;
	int			next_size;
	int			i;

	next_size = get_prime_size(table->size * 2);
	if (!(new = t_htable_create(next_size)))
		return (NULL);
	new->hash = table->hash;
	new->cmp = table->cmp;
	i = -1;
	while (++i < table->real_size)
	{
		if (table->table[i])
		{
			t_htable_add(table->hash(table->table[i], new->size),
					table->table[i], &new);
		}
	}
	t_htable_remove(table);
	return (new);
}

int				t_htable_add(int hash, void *pointer, t_htable **table)
{
	int			i;

	i = 0;
	if ((*table)->counter >= (*table)->size / 2)
	{
		*table = t_htable_resize(*table);
		hash = (*table)->hash(pointer, (*table)->size);
	}
	while (i + hash < (*table)->real_size)
	{
		if (!(*table)->table[hash + i])
		{
			(*table)->table[hash + i] = pointer;
			(*table)->counter++;
			return (1);
		}
		else if (!((*table)->cmp((*table)->table[hash + i], pointer)))
			return (0);
		i++;
	}
	*table = t_htable_resize(*table);
	t_htable_add(hash, pointer, table);
	return (0);
}

int				t_htable_find(int hash, void *pointer, t_htable *table)
{
	int			i;

	i = 0;
	while (hash + i < table->real_size)
	{
		if (!table->table[hash + i])
			return (0);
		else if (!(table->cmp(table->table[hash + i], pointer)))
			return (hash + i);
		i++;
	}
	return (0);
}

t_htable		*t_htable_init(int size, t_htable_cmp *cmp, t_htable_hash *hash)
{
	t_htable	*t;

	t = t_htable_create(size);
	t->cmp = cmp;
	t->hash = hash;
	return (t);
}

void			t_htable_free(t_htable *table)
{
	int			i;

	i = table->real_size;
	while (--i > -1)
	{
		if (table->table[i])
			free(table->table[i]);
	}
	free(table->table);
	free(table);
}
