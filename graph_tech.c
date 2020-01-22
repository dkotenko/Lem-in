#include "lem-in.h"
#include "libft/libft.h"

t_room	*ft_cpy_room(t_room *src)
{
	t_room *dst;
	int i;

	i = 0;
	dst	= malloc(sizeof(t_room));
	dst->name = ft_strdup(src->name);
	dst->x = src->x;
	dst->y = src->y;
	dst->s_lnk.links = (int*)malloc(sizeof(int) * src->s_lnk.max_size);
	dst->s_lnk.weights = (int*)malloc(sizeof(int) * src->s_lnk.max_size);
	dst->s_lnk.room_copy = -1;
	dst->s_lnk.is_copy = src->s_lnk.is_copy;
	while (i < src->s_lnk.cur_size)
	{
		dst->s_lnk.links[i] = src->s_lnk.links[i];
		dst->s_lnk.weights[i] = src->s_lnk.weights[i];
		i++;
	}
	dst->s_lnk.cur_size = src->s_lnk.cur_size;
	dst->s_lnk.max_size = src->s_lnk.max_size;
	dst->s_lnk.order = src->s_lnk.order;
	dst->flag = src->flag;
	return (dst);
}

t_array *ft_cpy_graph(t_array *arr)
{
	int i;
	t_array *result;

	result = malloc(sizeof(t_array));
	result->current = arr->current;
	result->finish = arr->finish;
	result->start = arr->start;
	result->base = arr->base;
	result->ants = arr->ants;
	result->max = arr->max;
	result->rooms = malloc(sizeof(t_room*) * arr->max);
	i = 0;
	while(i < arr->current)
	{
		result->rooms[i] = ft_cpy_room(arr->rooms[i]);
		i++;
	}
	while (i < result->max)
	{
		result->rooms[i] = NULL;
		i++;
	}
	return (result);
}

void	ft_clear_order(t_array **arr)
{
	int i;

	i = 0;
	while (i < (*arr)->current)
	{
		if ((*arr)->rooms[i])
		{
			(*arr)->rooms[i]->s_lnk.order = -1;
//			(*arr)->rooms[i]->flag = -1;
		}
		i++;
	}
}