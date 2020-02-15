/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_tech.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:42:52 by edrowzee          #+#    #+#             */
/*   Updated: 2020/02/12 13:42:53 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/libft.h"

void	reset_order_src(t_array **arr)
{
	int i;

	i = 0;
	while (i < (*arr)->current)
	{
		(*arr)->rooms[i]->order = INT_MAX;
		(*arr)->rooms[i]->src = -1;
		i++;
	}
}

void	ft_reset_graph(t_array **arr)
{
	int i;
	int j;

	i = -1;
	while (++i < (*arr)->base)
	{
		j = -1;
		while (++j < (*arr)->rooms[i]->s_lnk.cur_size)
		{
			(*arr)->rooms[i]->s_lnk.weights[j] = 1;
			if ((*arr)->rooms[i]->s_lnk.links[j] >= (*arr)->base)
				(*arr)->rooms[i]->s_lnk.links[j] =
			(*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->s_lnk.room_copy;
		}
		(*arr)->rooms[i]->s_lnk.room_copy = -1;
	}
	while (i < (*arr)->current)
	{
		ft_delete_room((*arr)->rooms[i]);
		(*arr)->rooms[i] = NULL;
		i++;
	}
	(*arr)->current = (*arr)->base;
}

void	ft_delete_room(t_room *room)
{
	free(room->s_lnk.links);
	free(room->s_lnk.weights);
	free(room);
}

void	ft_replace_cpy_in_path(t_array **arr, t_path *path)
{
	int i;

	i = 0;
	while (i < path->size)
	{
		if ((*arr)->rooms[path->path[i]]->s_lnk.is_copy == 1)
			path->path[i] = (*arr)->rooms[path->path[i]]->s_lnk.room_copy;
		i++;
	}
}
