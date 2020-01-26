#include "../includes/lem-in.h"
#include "../libft/libft.h"

void	reset_order_src(t_array **arr)
{
	int i;

	i = 0;
	while (i< (*arr)->current)
	{
		(*arr)->rooms[i]->order = INT_MAX;
		(*arr)->rooms[i]->src = -1;
		i++;
	}
}

t_path	*find_path_bf_new_ret(t_array **arr)
{
	t_path 	*result;
	int 	i;
	int		len;

	result = (t_path *)malloc(sizeof(t_path));
	i = (*arr)->finish;
	len = 1;
	while (i != (*arr)->start)
	{
		i = (*arr)->rooms[i]->src;
		len++;
	}
	result->size = len;
	//printf("size: %d\n", len);
	result->path = (int*)malloc(sizeof(int) * result->size);
	i = 1;
	result->path[0] = (*arr)->finish;
	result->curr_size = 0;
	while (i < result->size)
	{
		result->path[i] = (*arr)->rooms[result->path[i - 1]]->src;
		i++;
	}
	return (result);
}

void	find_path_bf_new_cycle(t_array **arr, int *is_weight_modify)
{
	int i;
	int j;

	i = 0;
	while (i < (*arr)->current)
	{
		j = 0;
		if ((*arr)->rooms[i]->order != INT_MAX)
			while (j < (*arr)->rooms[i]->s_lnk.cur_size)
			{
				if ((*arr)->rooms[i]->s_lnk.weights[j] != -2)
				{
					if ((*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->order > (*arr)->rooms[i]->order + (*arr)->rooms[i]->s_lnk.weights[j])
					{
						if ((*arr)->rooms[i]->s_lnk.weights[j] == 0)
						{
							(*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->order = (*arr)->rooms[i]->order;
							(*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->src = (*arr)->rooms[i]->src;
						}
						else
						{
							(*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->order = (*arr)->rooms[i]->order + (*arr)->rooms[i]->s_lnk.weights[j];
							(*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->src = i;
						}
						*is_weight_modify = 1;
					}
				}
				j++;
			}
		i++;
	}
}

t_path	*find_path_bf_new(t_array **arr)
{
	t_path	*result;
	int		i;
	int		is_weight_modify;

	i = 0;
	is_weight_modify = 1;
	(*arr)->rooms[(*arr)->start]->order = 0;
	while (i < (*arr)->current && is_weight_modify)
	{
		is_weight_modify = 0;
		find_path_bf_new_cycle(arr, &is_weight_modify);
		i++;
	}
	if ((*arr)->rooms[(*arr)->finish]->order == INT_MAX)
		return (NULL);
	result = find_path_bf_new_ret(arr);
	reset_order_src(arr);
//	printf("new path: ");
//	print_t_path(result, *arr);
	return (result);
}

void	ft_delete_room(t_room *room)
{
	free(room->s_lnk.links);
	free(room->s_lnk.weights);
	free(room->name);
	free(room);
}

void	ft_reset_graph(t_array **arr)
{
	int i;
	int j;

	i = 0;
	while (i < (*arr)->base)
	{
		j = 0;
		while (j < (*arr)->rooms[i]->s_lnk.cur_size)
		{
			(*arr)->rooms[i]->s_lnk.weights[j] = 1;
			if((*arr)->rooms[i]->s_lnk.links[j] >= (*arr)->base)
				(*arr)->rooms[i]->s_lnk.links[j] = (*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->s_lnk.room_copy;
			j++;
		}
		(*arr)->rooms[i]->s_lnk.room_copy = -1;
		i++;
	}
	while (i < (*arr)->current)
	{
		ft_delete_room((*arr)->rooms[i]);
		(*arr)->rooms[i] = NULL;
		i++;
	}
	(*arr)->current = (*arr)->base;
}

int    main(int argc, char **argv)
{
	t_array	*arr;
	t_array	*arr_not_expanded;
	t_paths	*paths;
	t_paths	*prev;
//	t_array *test;
	int i = 0;
	int 	path_counter;
	int path_limit;
	ft_reader(argc, argv, &arr);
	paths = create_t_paths();
	arr_not_expanded = get_copy_t_array(arr);
	path_counter = 0;
	path_limit = ft_path_limit(arr);
	arr->base = arr->current;
//	test = ft_cpy_graph(arr);
	while (path_counter < path_limit)
	{

		if (path_counter)
			prev = copy_t_paths(paths);
		i = 0;

		while (i < paths->curr_path)
		{
			ft_expand_graph(&arr, paths->path_arr[i]->path, paths->path_arr[i]->size);
			i++;
		}
		paths->path_arr[paths->curr_path] = find_path_bf_new(&arr);
		ft_clear_order(&arr);
		if (!paths->path_arr[paths->curr_path])
			break;
//		ft_expand_graph(&arr, paths->path_arr[paths->curr_path]->path, paths->path_arr[paths->curr_path]->size);
		ft_check_for_cpy_bfs_smart(&arr, paths->path_arr[paths->curr_path]);

		paths->curr_path++;
//		find_path_bf_new(&arr);
		//handle_paths(arr_not_expanded, arr, paths);

		printf("Before merge_paths\n");
		print_t_paths(paths, arr);
		printf("//////////\n");
		while (merge_paths(arr, paths))
			;
		printf("AFTER merge_paths\n");
		print_t_paths(paths, arr);
		printf("//////////\n");

		paths->time = ft_calc_path_time(&arr, paths);
		if (path_counter)
		{
			if (paths->time >= prev->time)
			{
				paths = prev;
				break;
			}
			else
			{
				free(prev);
				prev = copy_t_paths(paths);
			}
		}
		ft_reset_graph(&arr);
//		arr = ft_cpy_graph(test);
		path_counter++;
	}
//	i = 0;
//
//	while (i < paths->curr_path)
//	{
//		ft_expand_graph(&arr, paths->path_arr[i]->path);
//		i++;
//	}
//
//	print_t_array_rooms_with_links(arr);
	ft_ants_prepare_to_parade(&arr, paths);
	return (0);
}