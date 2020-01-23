#include "../includes/lem-in.h"
#include "../libft/libft.h"

int    main(int argc, char **argv)
{
	t_array	*arr;
	t_array	*arr_not_expanded;
	t_paths	*paths;
	t_paths	*prev;
	t_array *test;
	int i = 0;
	int 	path_counter;
	int path_limit;
	ft_reader(argc, argv, &arr);
	paths = create_t_paths();
	arr_not_expanded = get_copy_t_array(arr);
	path_counter = 0;
	path_limit = ft_path_limit(arr);
	arr->base = arr->current;
	test = ft_cpy_graph(arr);
	while (path_counter < path_limit)
	{

		if (path_counter)
			prev = copy_t_paths(paths);
		i = 0;

		while (i < paths->curr_path)
		{
			ft_expand_graph(&arr, paths->path_arr[i]->path);
			i++;
		}
		//printf("%d\n", check++);
		paths->path_arr[paths->curr_path] = ft_find_path_bf(&arr, 1);
		ft_clear_order(&arr);

		ft_check_for_cpy_bfs_smart(&arr, paths->path_arr[paths->curr_path]);
		if (!paths->path_arr[paths->curr_path])
			break;
		paths->curr_path++;

		handle_paths(arr_not_expanded, arr, paths);
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
		arr = ft_cpy_graph(test);
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