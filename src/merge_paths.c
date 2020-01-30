#include "includes/lem-in.h"

static t_path		*join_free_t_path(t_path **path1, t_path **path2)
{
	t_path	*new;
	int 	i;
	int 	j;
	
	i = 0;
	new = t_path_create((*path1)->size + (*path2)->size);
	while (i < (*path1)->size)
	{
		new->path[i] = (*path1)->path[i];
		i++;
	}
	j = 0;
	while (j < (*path2)->size)
	{
		new->path[i] = (*path2)->path[j];
		i++;
		j++;
	}
	t_path_free(*path1);
	t_path_free(*path2);	
	return (new);
}

static t_path		*slice_t_path(t_path *path, int start, int end)
{
	t_path	*new;
	int 	i;

	if (end < start || start < 0)
	{
		ft_putstr_fd("ERROR: slice_t_path out of bounds\n", 2);
		return (NULL);
	}
	i = 0;
	new = t_path_create(end - start);	
	while (start < end)
	{
		new->path[i] = path->path[start];
		i++;
		start++;
	}	
	//printf("size: %d\n", new->size);
	return (new);
}

static void	merge_int_paths(t_path **path1, t_path **path2, int path1_ind1, int path2_ind1, t_array *arr)
{
	t_path	*temp1;
	t_path	*temp2;
	t_path *slice_temp1;
	t_path *slice_temp2;
	temp1 = *path1;
	temp2 = *path2;
	if (arr->current > 20000000)
		printf("hello");	
	slice_temp1 = slice_t_path(temp1,  0, path1_ind1);
	slice_temp2 = slice_t_path(temp2, nbr_in_array_pos(
			temp1->path[path1_ind1], temp2->path, temp2->size), temp2->size);	
	*path1 = join_free_t_path(&slice_temp1, &slice_temp2);	
	slice_temp1 = slice_t_path(temp2, 0, path2_ind1);	
	slice_temp2 = slice_t_path(temp1, nbr_in_array_pos(
			temp2->path[path2_ind1], temp1->path, temp1->size), temp1->size);	
	*path2 = join_free_t_path(&slice_temp1, &slice_temp2);
	t_path_free(temp1);
	t_path_free(temp2);	
}

static int 	get_index_of_intersection_in_path(t_path *path1, t_path *path2, t_array *arr)
{
	int	i;
	int j;
	int p1_orig;
	int p2_orig;

	i = 0;
	while (++i < path1->size - 1)
	{
		j = path2->size - 1;
		p1_orig = get_origin_room(path1->path[i], arr);
		while (--j > 0)
		{
			p2_orig = get_origin_room(path2->path[j], arr);
			if (p1_orig == p2_orig && get_origin_room(path2->path[j - 1], arr)
			== get_origin_room(path1->path[i + 1], arr))
				return (i);
		}
	}
	return (0);
}

int		merge_paths(t_array *arr, t_paths *paths)
{
	int	i;
	int j;
	int p1_ind1;
	int p2_ind1;
	int switched;

	switched = 0;
	i = -1;
	while (++i < paths->curr_path - 1)
	{
		j = i;
		while (++j < paths->curr_path)
		{
			p1_ind1 = get_index_of_intersection_in_path(paths->path_arr[i],
					paths->path_arr[j], arr);
			if (p1_ind1)
			{
				p2_ind1 = get_index_of_intersection_in_path(paths->path_arr[j],
															paths->path_arr[i], arr);
				/*p2_ind1 = nbr_in_array_pos(paths->path_arr[i]->path[p1_ind1],
						paths->path_arr[j]->path, paths->path_arr[j]->size);*/
				merge_int_paths(&paths->path_arr[i], &paths->path_arr[j],
								p1_ind1, p2_ind1, arr);
				switched = 1;
			}
		}
	}
	return (switched);
}