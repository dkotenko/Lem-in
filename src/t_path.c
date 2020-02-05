#include "includes/lem-in.h"

int			t_path_has_duplicates(t_path *path)
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

t_path		*t_path_create(int size)
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	new->path = (int *)malloc(sizeof(int) * size);
	new->curr_size = 0;
	new->size = size;
	new->order = 1;
	return (new);
}

t_path		*copy_t_path(t_path *path)
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	new->size = path->size;
	new->path = copy_int_array(path->path, path->size);
	new->curr_size = path->curr_size;
	new->order = path->order;
	return (new);
}

void		t_path_free(t_path *path)
{
	free(path->path);
	free(path);
}

void		ft_path_sort(t_path *path)
{
	int	temp[path->size];
	int i;
	int j;
	i = 0;
	j = path->size - 1;
	while (i < path->size)
	{
		temp[i] = path->path[j];
		j--;
		i++;
	}
	i = 0;
	while (i < path->size)
	{
		path->path[i] = temp[i];
		i++;
	}
}