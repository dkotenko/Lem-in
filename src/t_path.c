#include "includes/lem-in.h"

int t_path_has_duplicates(t_path *path)
{
	int 	i;
	int		j;

	i = -1;

	while(++i < path->size)
	{
		j = i;
		while (++j < path->size)
		{
			if (path->path[i] == path->path[j])
				return (1);
		}
	}
	return (0);
}

t_path *t_path_create(int size)
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	new->path = (int *)malloc(sizeof(int) * size);
	new->curr_size = 0;
	new->size = size;
	new->order = 1;
	return (new);
}

t_path *copy_t_path(t_path *path)
{
	t_path *new;

	new = (t_path *)malloc(sizeof(t_path));
	new->size = path->size;
	new->path = copy_int_array(path->path, path->size);
	new->curr_size = path->curr_size;
	new->order = path->order;
	return (new);
}