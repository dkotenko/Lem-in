#include "../includes/lemin.h"

void	t_htables_init(t_input *input, int size, t_htable_cmp *cmp, t_htable_hash *hash)
{
	input->ht->coords = t_htable_init(size, cmp, hash);
	input->ht->names = t_htable_init(size, cmp, hash);
	input->ht->links = t_htable_init(size, cmp, hash);
}

void	t_htables_free(t_htables *ht)
{
	t_htable_free(ht->names);	
	free(ht->links);
	free(ht->coords);
	free(ht);
}

