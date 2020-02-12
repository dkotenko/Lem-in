/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:15:40 by edrowzee          #+#    #+#             */
/*   Updated: 2020/02/12 13:15:41 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/libft.h"

void	ft_expand_graph3(t_array **arr, int *p, int size)
{
	int		i;
	int		j;
	t_room	**r;

	r = (*arr)->rooms;
	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < r[p[i]]->s_lnk.cur_size)
		{
			if (r[p[i]]->s_lnk.links[j] == p[i + 1]
			&& p[i + 1] != (*arr)->start)
				r[p[i]]->s_lnk.links[j] = r[p[i + 1]]->s_lnk.room_copy;
			if (i != 0 && r[p[i]]->s_lnk.weights[j] == 1)
				r[p[i]]->s_lnk.weights[j] = -2;
			if (i != 0 && r[r[p[i]]->s_lnk.room_copy]->s_lnk.weights[j] == -1 &&
	(r[p[i]]->s_lnk.room_copy > r[r[p[i]]->s_lnk.room_copy]->s_lnk.room_copy))
				r[r[p[i]]->s_lnk.room_copy]->s_lnk.weights[j] = -2;
		}
		if (r[p[i]]->s_lnk.room_copy != -1 && (r[p[i]]->s_lnk.room_copy
		> r[r[p[i]]->s_lnk.room_copy]->s_lnk.room_copy))
			ft_links_push(&(r[r[p[i]]->s_lnk.room_copy]->s_lnk), p[i], 0);
	}
}

void	ft_expand_graph2(t_array **arr, int *path, int size)
{
	int		i;
	t_room	*room;

	i = 0;
	while (++i < size - 1)
	{
		if ((*arr)->rooms[path[i]]->s_lnk.room_copy == -1)
		{
			room = (t_room*)malloc((sizeof(t_room)));
			ft_cpy_room_data(room, (*arr)->rooms[path[i]],
					(*arr)->current, path[i]);
			ft_arr_push(arr, room);
		}
	}
}

void	ft_expand_graph(t_array **arr, int *path, int size)
{
	int		i;
	int		j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < (*arr)->rooms[path[i]]->s_lnk.cur_size)
		{
			if (i != 0 && (*arr)->rooms[path[i]]->s_lnk.links[j] == path[i - 1])
				(*arr)->rooms[path[i]]->s_lnk.weights[j] = -2;
			if (i < size - 1 && (*arr)->rooms[path[i]]->s_lnk.links[j]
				== path[i + 1])
				(*arr)->rooms[path[i]]->s_lnk.weights[j] = -1;
		}
	}
	ft_expand_graph2(arr, path, size);
	ft_expand_graph3(arr, path, size);
}
