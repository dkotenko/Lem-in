#include "../includes/lem-in.h"
#include "../libft/libft.h"

int		*copy_int_array(int *arr, int size)
{	
	int i;
	int *new;

	new = (int *)malloc(sizeof(int) * (size + 1));
	ft_fill_mem(new, size + 1, -1);
	i = 0;
	while (i < size)
	{
		new[i] = arr[i];
		i++;
	}
	return (new);
}

int     nbr_in_array_pos(int number, int *arr, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (arr[i] == number)
			return (i);
		i++;
	}
	return (-1);
}

int     nbr_in_links_pos(t_array *arr , int curr, int link)
{
	int link_index;
	int i;

	link_index = arr->rooms[curr]->s_lnk.links[link];
	i = 0;
	while (i < arr->rooms[link_index]->s_lnk.cur_size)
	{
		if (arr->rooms[link_index]->s_lnk.links[i] == curr)
			return (i);
		i++;
	}
	return (-1);
}

int 	get_common_vertices_nbr(t_path *path1, t_path *path2, int path1_ind1, int path2_ind1)
{
	int 	i;

	i = 0;
	while (path1->path[path1_ind1] == path2->path[path2_ind1])
	{
		i++;
		path1_ind1++;
		path2_ind1++;
	}
	return (i);
}

int		ft_free(void *val)
{
	free(val);
	return (1);
}



