#include "../includes/lem-in.h"

void	t_htables_init(t_input *input, int size, t_htable_cmp *cmp, t_htable_hash *hash)
{
	input->ht->coords = t_htable_init(size, cmp, hash);
	input->ht->names = t_htable_init(size, cmp, hash);
	input->ht->links = t_htable_init(size, cmp, hash);
}

