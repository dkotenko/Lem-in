#include "../includes/lem-in.h"

int				cmp_func(const void* a, const void* b)
{
	return (ft_strcmp((const char*)a, (const char*)b));
}

int				hash_func(const void* p, int size)
{
	int			i;
	intmax_t	hash;
	int			len;
	const char* s;

	s = (const char*)p;
	hash = 1;
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		hash *= ((hash * (intmax_t)INIT_PRIME_NUMBER) + (intmax_t)s[i]) % (intmax_t)size;
		i++;
	}
	if (hash == 0)
		hash = 1;
	if (hash < 0)
		return ((hash % size) * -1);
	return (hash % size);
}

int				is_prime_number(int n)
{
	int			i;

	if (n == 1)
		return 0;	
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

t_htable 		*t_htable_resize(t_htable *table)
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
			t_htable_add(table->hash(table->table[i], new->size), table->table[i], &new);
		}
	}
	t_htable_remove(table);
	return (new);	
}

int			t_htable_add(int hash, void *pointer, t_htable **table)
{
	int		i;

	i = 0;
	//printf("%p pointer to add \n", pointer);
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

	i  = 0;
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
		
	free(table);
}
