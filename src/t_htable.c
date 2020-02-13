/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_htable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:47:48 by clala             #+#    #+#             */
/*   Updated: 2020/02/13 19:47:06 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int				cmp_func(const void *a, const void *b)
{
	return (ft_strcmp((const char *)a, (const char *)b));
}

int				is_prime_number(int n)
{
	int			i;

	if (n == 1)
		return (0);
	i = 2;
	while (i * i <= n)
	{
		if (!(n % i))
			return (0);
		i++;
	}
	return (1);
}

int				get_prime_size(int size)
{
	while (!is_prime_number(size))
		size++;
	return (size);
}

t_htable		*t_htable_create(int size)
{
	t_htable	*new;

	if (!(new = (t_htable *)malloc(sizeof(t_htable))))
		return (NULL);
	size = get_prime_size(size);
	new->real_size = get_prime_size(size + REAL_SIZE_OFFSET);
	new->table = (void **)malloc(sizeof(void *) * new->real_size);
	new->size = size;
	size = new->real_size;
	while (--size > -1)
	{
		new->table[size] = NULL;
	}
	new->counter = 0;
	return (new);
}

void			t_htable_remove(t_htable *table)
{
	free(table->table);
	free(table);
}
