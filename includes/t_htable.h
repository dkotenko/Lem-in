/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_htable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:07:29 by edrowzee          #+#    #+#             */
/*   Updated: 2020/02/13 21:04:13 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_HTABLE_H
# define T_HTABLE_H

# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define INIT_PRIME_NUMBER 353
# define REAL_SIZE_OFFSET 10

typedef int			t_htable_cmp(const void *p1, const void *p2);
typedef int			t_htable_hash(const void *p, int size);

typedef struct		s_hlist
{
	struct s_hlist	*next;
	void			*key;
	uintptr_t		val;
}					t_hlist;

typedef struct		s_htable {
	t_htable_cmp	*cmp;
	t_htable_hash	*hash;
	int				counter;
	int				size;
	int				real_size;
	void			**table;
}					t_htable;

int					t_htable_add(int hash, void *pointer,
					t_htable **hash_table);
t_htable			*t_htable_create(int size);
void				t_htable_remove(t_htable *table);
int					get_prime_size(int size);
t_htable			*t_htable_resize(t_htable *table);
int					t_htable_find(int hash, void *pointer, t_htable *table);
t_htable			*t_htable_init(int size, t_htable_cmp *cmp,
					t_htable_hash *hash);
int					cmp_func(const void*a, const void*b);
int					hash_func(const void*p, int size);
void				t_htable_free(t_htable *table);

#endif
