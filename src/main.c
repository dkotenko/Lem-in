#include "../includes/lem-in.h"

#include <time.h>
int    main(int argc, char **argv)
{
	// SPEED TEST
	clock_t start, end;
	double runTime;
	start = clock();
	//

	t_array	*arr;
//	t_array	*arr_not_expanded;
	t_paths	*paths;
	t_paths	*prev;
	t_input *input;
	arr = NULL;
	input = NULL;
	int i = 0;
	int 	path_counter;
	int path_limit;
	ft_arr_malloc(&arr);
	t_input_malloc(&input);
	ft_reader(argc, argv, input, arr);
	t_input_print(input);
	paths = create_t_paths();
//	arr_not_expanded = get_copy_t_array(arr);
	path_counter = 0;
	path_limit = ft_path_limit(arr);
	arr->base = arr->current;
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
		if (!paths->path_arr[paths->curr_path])
			break;
		ft_replace_cpy_in_path(&arr, paths->path_arr[paths->curr_path]);
		paths->curr_path++;
//		handle_paths(arr_not_expanded, arr, paths);

		/*printf("Before merge_paths\n");
		print_t_paths(paths, arr);
		int o = -1;
		while (++o < paths->curr_path)
		{
			if (t_path_has_duplicates(paths->path_arr[o]))
			{
				printf("DUPLICATE\n");
				print_t_path(paths->path_arr[o], arr);
				printf("//////////\n");
			}
		}
		printf("---------------\n");
*/
		while (merge_paths(arr, paths))
			; /*
		printf("AFTER merge_paths\n");
		print_t_paths(paths, arr);
		printf("---------------\n");
		o = -1;
		while (++o < paths->curr_path)
		{
			if (t_path_has_duplicates(paths->path_arr[o]))
			{
				printf("DUPLICATE\n");
				print_t_path(paths->path_arr[o], arr);
				printf("//////////\n");
			}
		}
*/
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

	// SPEED TIME
	end = clock();
	runTime = ((end - start) / (double) CLOCKS_PER_SEC );
	printf ("Run time is %g seconds\n", runTime);
	//
	return (0);
}