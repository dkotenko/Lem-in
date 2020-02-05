#include "includes/lem-in.h"

void		t_room_free(t_room *room)
{
	free(room->s_lnk.links);
	free(room->s_lnk.weights);
	free(room);
}

int 	    get_origin_room(int room_nb, t_array *arr)
{
	if (arr->rooms[room_nb]->s_lnk.is_copy)
		return (arr->rooms[room_nb]->s_lnk.room_copy);
	return (room_nb);
}

int 		room_in_no_expanded(t_array *arr_not_expanded, t_room *room)
{
	int	i;

	i = 0;
	while (i < arr_not_expanded->max)
	{		
		if (arr_not_expanded->rooms[i] && !ft_strcmp(room->name, arr_not_expanded->rooms[i]->name))
			return (1);
		i++;
	}
	return (0);
}

t_room		*copy_room_mod(t_room **rooms, int i)
{
	t_room	*room;

	room = (t_room*)malloc(sizeof(t_room));
	if (rooms[i]->s_lnk.is_copy)
		i = rooms[i]->s_lnk.room_copy;
	room->name = rooms[i]->name;
	room->s_lnk.links = (int *) malloc(sizeof(int) * (rooms[i]->s_lnk.cur_size));
	room->s_lnk.weights = (int *) malloc(sizeof(int) * (rooms[i]->s_lnk.cur_size));
	ft_fill_mem(room->s_lnk.links, rooms[i]->s_lnk.cur_size, -1);
	room->s_lnk.room_copy = -1;
	room->s_lnk.is_copy = 0;
	room->s_lnk.max_size = rooms[i]->s_lnk.cur_size;
	room->s_lnk.cur_size = 0;
	return (room);
}