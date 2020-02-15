/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_htables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:47:48 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 14:34:32 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			t_htables_init(t_input *input, int size, t_htable_cmp *cmp,
						t_htable_hash *hash)
{
	input->ht->coords = t_htable_init(size, cmp, hash);
	input->ht->names = t_htable_init(size, cmp, hash);
	input->ht->links = t_htable_init(size, cmp, hash);
}

void			t_htables_free(t_htables *ht)
{
	t_htable_free(ht->names);
	free(ht->links->table);
	free(ht->links);
	free(ht->coords->table);
	free(ht->coords);
	free(ht);
}

int				hash_func(const void *p, int size)
{
	int			i;
	intmax_t	hash;
	int			len;
	const char	*s;

	s = (const char*)p;
	hash = 1;
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		hash *= (((hash * (intmax_t)INIT_PRIME_NUMBER)
			+ (intmax_t)s[i]) % (intmax_t)size);
		i++;
	}
	if (hash == 0)
		hash = 1;
	if (hash < 0)
		return ((hash % size) * -1);
	return (hash % size);
}
