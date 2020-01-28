#include "../includes/lem-in.h"
#include "../libft/libft.h"

void 	ft_expand_graph3(t_array **arr, int *path, int size)
{
	int i;
	int j;

	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < (*arr)->rooms[path[i]]->s_lnk.cur_size)
		{
			if ((*arr)->rooms[path[i]]->s_lnk.links[j] == path[i + 1] && path[i + 1] != (*arr)->start)
				(*arr)->rooms[path[i]]->s_lnk.links[j] = (*arr)->rooms[path[i + 1]]->s_lnk.room_copy;
			if (i != 0 && (*arr)->rooms[path[i]]->s_lnk.weights[j] == 1)
				(*arr)->rooms[path[i]]->s_lnk.weights[j] = -2;
			if (i != 0 && (*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.weights[j] == -1 && ((*arr)->rooms[path[i]]->s_lnk.room_copy > (*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.room_copy))
				(*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.weights[j] = -2;
		}
		if ((*arr)->rooms[path[i]]->s_lnk.room_copy != -1 && ((*arr)->rooms[path[i]]->s_lnk.room_copy > (*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.room_copy))
			ft_links_push(&((*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk), path[i], 0);
	}
}

void 	ft_expand_graph2(t_array **arr, int *path, int size)
{
	int		i;
	t_room	*room;

	i = 0;
	while (++i < size - 1)
	{
		if ((*arr)->rooms[path[i]]->s_lnk.room_copy == -1)
		{
			room = (t_room*)malloc((sizeof(t_room)));
			ft_cpy_room_data(room, (*arr)->rooms[path[i]], (*arr)->current, path[i]);
			ft_arr_push(arr, room);
		}
	}
}

void	ft_expand_graph(t_array **arr, int *path, int size)
{
	int		i;
	int 	j;


	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < (*arr)->rooms[path[i]]->s_lnk.cur_size)
		{
			if (i != 0 && (*arr)->rooms[path[i]]->s_lnk.links[j] == path[i - 1])
				(*arr)->rooms[path[i]]->s_lnk.weights[j] = -2;
			if (i < size - 1 && (*arr)->rooms[path[i]]->s_lnk.links[j] == path[i + 1])
					(*arr)->rooms[path[i]]->s_lnk.weights[j] = -1;
		}
	}
	ft_expand_graph2(arr, path, size);
	ft_expand_graph3(arr, path, size);
}
