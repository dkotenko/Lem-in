/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:06:05 by edrowzee          #+#    #+#             */
/*   Updated: 2020/02/15 14:46:58 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include <time.h>

static int	ft_path_limit(t_array *arr)
{
	int		min;

	min = INT_MAX;
	if (min > arr->rooms[arr->start]->s_lnk.cur_size)
		min = arr->rooms[arr->start]->s_lnk.cur_size;
	if (min > arr->rooms[arr->finish]->s_lnk.cur_size)
		min = arr->rooms[arr->finish]->s_lnk.cur_size;
	if (min == 0)
	{
		ft_printf("Error: no paths in graph\n");
		exit(1);
	}
	if (min > arr->ants)
		min = arr->ants;
	return (min);
}

static int	paths_work(t_paths **paths, t_paths **prev, int *path_counter)
{
	if (*path_counter && (*paths)->time > (*prev)->time)
	{
		t_paths_free(*paths);
		*paths = *prev;
		return (0);
	}
	else if (*path_counter)
		t_paths_free(*prev);
	(*path_counter)++;
	return (1);
}

static int	graph_work(t_array *arr, t_paths *paths)
{
	int		i;

	i = 0;
	while (i < paths->curr_path)
	{
		ft_expand_graph(&arr, paths->path_arr[i]->path,
				paths->path_arr[i]->size);
		i++;
	}
	paths->path_arr[paths->curr_path] = find_path_bf_new(&arr);
	if (paths->curr_path == 0 && !paths->path_arr[paths->curr_path])
	{
		ft_printf("Error: no paths found\n");
		exit(1);
	}
	if (!paths->path_arr[paths->curr_path])
		return (0);
	ft_replace_cpy_in_path(&arr, paths->path_arr[paths->curr_path]);
	paths->curr_path++;
	while (merge_paths(arr, paths))
		;
	paths->time = ft_calc_path_time(&arr, paths, -1, -1);
	ft_reset_graph(&arr);
	return (1);
}

static void	validate_input(t_array *arr, int argc, char **argv, t_input **input)
{
	t_input_malloc(input);
	ft_reader(argc, argv, *input, arr);
	t_input_print(*input);
}

int			main(int argc, char **argv)
{
	t_array	*arr;
	t_paths	*paths;
	t_paths	*prev;
	int		path_counter;
	t_input	*input;

	arr = NULL;
	ft_arr_malloc(&arr);
	input = NULL;
	validate_input(arr, argc, argv, &input);
	paths = create_t_paths();
	path_counter = 0;
	arr->path_limit = ft_path_limit(arr);
	arr->base = arr->current;
	while (path_counter < arr->path_limit)
	{
		if (path_counter)
			prev = copy_t_paths(paths);
		if (graph_work(arr, paths) == 0 || paths_work(&paths,
				&prev, &path_counter) == 0)
			break ;
	}
	ft_ants_prepare_to_parade(&arr, paths, -1);
	t_input_free(input);
	exit(0);
}
