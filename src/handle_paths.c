/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:47:48 by clala             #+#    #+#             */
/*   Updated: 2020/02/05 21:00:57 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem-in.h"

void				delete_edges_bf(t_array *arr, t_path *path, t_deleted_edges *edges)
{
	int				index_first;
	int				i;

	i = -1;
	while (++i + 1 < path->size)
	{
		index_first = nbr_in_array_pos(path->path[i + 1],
									   arr->rooms[path->path[i]]->s_lnk.links,
									   arr->rooms[path->path[i]]->s_lnk.cur_size);
		if (index_first == -1)
			continue ;
		arr->rooms[path->path[i]]->s_lnk.weights[index_first] = -2;
		edges->edge_rooms[edges->curr_size] = path->path[i];
		edges->edge_indexes[edges->curr_size] = index_first;
		edges->curr_size++;
	}
}

void				restore_edges_bf(t_array *arr, t_deleted_edges *edges)
{
	int				i;

	i = -1;
	while (++i < edges->curr_size)
	{
		arr->rooms[edges->edge_rooms[i]]->s_lnk.weights[edges->edge_indexes[i]] = 1;
	}
}

void				delete_double_links(t_array *arr)
{
	int				i;
	int				j;
	int				pos_i_in_links_j;
	int				pos_j_in_rooms;

	i = -1;
	while (++i < arr->current)
	{
		if (!arr->rooms[i])
			continue ;
		j = -1;
		while (++j < arr->rooms[i]->s_lnk.cur_size)
		{
			pos_i_in_links_j = nbr_in_links_pos(arr, i, j);
			pos_j_in_rooms = arr->rooms[i]->s_lnk.links[j];
			if (pos_i_in_links_j != -1 &&
			arr->rooms[pos_j_in_rooms]->s_lnk.weights[pos_i_in_links_j] != -2
			&& arr->rooms[i]->s_lnk.weights[j] != -2)
			{
				arr->rooms[pos_j_in_rooms]->s_lnk.weights[pos_i_in_links_j] = -2;
				arr->rooms[i]->s_lnk.weights[j] = -2;
			}
		}
	}
}

void				handle_paths(t_array *arr_not_expanded, t_array *arr, t_paths *paths)
{
	int				i;
	t_path			*tmp;
	t_deleted_edges	*deleted_edges;

	add_path_to_no_expanded(arr_not_expanded, arr, paths->path_arr[paths->curr_path - 1]);
	delete_double_links(arr_not_expanded);
	deleted_edges = t_deleted_edges_create(arr_not_expanded->current);
	i = -1;

	while (++i < paths->curr_path)
	{
		tmp = paths->path_arr[i];
		paths->path_arr[i] = ft_find_path_dfs(&arr_not_expanded);
		if (!paths->path_arr[i])
		{
			paths->curr_path = i;
			break;
		}
		delete_edges_bf(arr_not_expanded, paths->path_arr[i], deleted_edges);
		t_path_free(tmp);
	}
	if (deleted_edges->curr_size)	
		restore_edges_bf(arr_not_expanded, deleted_edges);
	t_deleted_edges_free(&deleted_edges);
}

void				add_path_to_no_expanded(t_array *arr_not_expanded, t_array *arr, t_path *path)
{
	int				i;
	int				k;
	int				prev_index;

	i = path->size;
	while (--i > -1)
	{
		k = get_origin_room(path->path[i], arr);
		if (!room_in_no_expanded(arr_not_expanded, arr->rooms[k]))
			arr_not_expanded->rooms[k] = copy_room_mod(arr->rooms, k);
		if (i > 0)
		{
			prev_index = nbr_in_array_pos(path->path[i - 1],
					arr_not_expanded->rooms[k]->s_lnk.links,
					arr_not_expanded->rooms[k]->s_lnk.cur_size);
			if (prev_index == -1)
			{
				arr_not_expanded->rooms[k]->s_lnk.links[arr_not_expanded->rooms[k]->s_lnk.cur_size] = \
                get_origin_room(path->path[i - 1], arr);
				arr_not_expanded->rooms[k]->s_lnk.weights[arr_not_expanded->rooms[k]->s_lnk.cur_size++] = 1;				
			}
			else
				arr_not_expanded->rooms[k]->s_lnk.weights[prev_index] = 1;
		}
	}
}
