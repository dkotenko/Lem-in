#include "../includes/lem-in.h"
#include "../libft/libft.h"

void	ft_split_free(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}

t_room	**ft_rooms_copy(t_room **rooms, int size)
{
	int i;
	t_room		**new_rooms;

	i = 0;
	new_rooms = (t_room**)malloc(sizeof(t_room*) * size * 2);
	while (i < size)
	{
		new_rooms[i] = rooms[i];
		i++;
	}
	free(rooms);
	return (new_rooms);
}

void	ft_arr_malloc(t_array **arr)
{
	static int	size = ARR_INIT_SIZE;
//	int			i;

	if (*arr == NULL)
	{
		*arr = (t_array*)malloc(sizeof(t_array) * 1);
		(*arr)->rooms = (t_room**)malloc(sizeof(t_room*) * size);
		(*arr)->max = size;
		(*arr)->current = 0;
//		i = 0;
	}
	if ((*arr)->current == (*arr)->max)
	{
		size *= 2;
		(*arr)->rooms = ft_rooms_copy((*arr)->rooms, (*arr)->max);
//		i = (*arr)->max;
		(*arr)->max *= 2;
	}
//	while (i < size)
//		(*arr)->rooms[i++] = NULL;
	return ;
}

int		*ft_int_arr_realloc(int *arr, int new_size)
{
	int	*new_arr;
	int	i;

	new_arr = (int*)malloc(sizeof(int) * new_size);
	i = 0;
	while (i < new_size/2)
	{
		new_arr[i] = arr[i];
		i++;
	}
	free(arr);
	return(new_arr);
}

void	ft_links_push(t_links *s_lnk, int push, int weight)
{
	if (s_lnk->links == NULL)
	{
		s_lnk->links = (int*)malloc(sizeof(int) * s_lnk->max_size);
		s_lnk->weights = (int*)malloc(sizeof(int) * s_lnk->max_size);
	}
	else if (s_lnk->cur_size == s_lnk->max_size)
	{
		s_lnk->max_size *= 2;
		s_lnk->links = ft_int_arr_realloc(s_lnk->links, s_lnk->max_size);
		s_lnk->weights = ft_int_arr_realloc(s_lnk->weights, s_lnk->max_size);
	}
	s_lnk->links[s_lnk->cur_size] = push;
	s_lnk->weights[s_lnk->cur_size] = weight;
	(s_lnk->cur_size)++;
}

void	ft_arr_push(t_array **arr, t_room *room)
{

	if (*arr == NULL || (*arr)->current == (*arr)->max)
		ft_arr_malloc(arr);

	(*arr)->rooms[(*arr)->current] = room;

	(*arr)->current++;

}

void	ft_read_ants(int fd, t_array **arr)
{
	char	*temp;
	int		ants;

	get_next_line(fd, &temp);
	ants = ft_atoi(temp);
	free(temp);
	ft_arr_malloc(arr);
	(*arr)->ants = ants;
}

void	ft_create_room(t_array **arr, char **split, int *flag)
{
	t_room *room;

	room = (t_room*)malloc(sizeof(t_room));
	room->name = NULL;
	room->name = ft_strdup(split[0]);
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	room->flag = -1;
	room->s_lnk.cur_size = 0;
	room->s_lnk.max_size = ARR_INIT_SIZE;
	room->s_lnk.order = -1;
	room->s_lnk.room_copy = -1;
	room->s_lnk.links = NULL;
	room->s_lnk.is_copy = 0;
	ft_arr_push(arr, room);
	if (*flag == 1)
		(*arr)->start = (*arr)->current - 1;
	else if (*flag == 2)
		(*arr)->finish = (*arr)->current - 1;
	*flag = 0;
}

void	ft_cpy_room_data(t_room *dst, t_room *src, int ds, int sr)
{
	int i;

	i = 0;
	dst->name = ft_strjoin("#", src->name);
	dst->x = src->x;
	dst->y = src->y;
	dst->s_lnk.links = (int*)malloc(sizeof(int) * src->s_lnk.max_size);
	dst->s_lnk.weights = (int*)malloc(sizeof(int) * src->s_lnk.max_size);
	dst->s_lnk.room_copy = sr;
	src->s_lnk.room_copy = ds;
	dst->s_lnk.is_copy = 1;
	while (i < src->s_lnk.cur_size)
	{
		dst->s_lnk.links[i] = src->s_lnk.links[i];
		dst->s_lnk.weights[i] = src->s_lnk.weights[i];
		i++;
	}
	dst->s_lnk.cur_size = src->s_lnk.cur_size;
	dst->s_lnk.max_size = src->s_lnk.max_size;
	dst->s_lnk.order = src->s_lnk.order;
}

void	ft_create_links(t_array **arr, char **split)
{
	char	**links;
	int		i;
	int		first_room;
	int 	second_room;

	i = 0;
	links = ft_strsplit(split[0], '-');
	while (i < (*arr)->current)
	{
		if (!(ft_strcmp(links[0], (*arr)->rooms[i]->name)))
			first_room = i;
		if (!(ft_strcmp(links[1], (*arr)->rooms[i]->name)))
			second_room = i;
		i++;
	}
	ft_links_push(&((*arr)->rooms[first_room]->s_lnk), second_room, 1);
	ft_links_push(&((*arr)->rooms[second_room]->s_lnk), first_room, 1);
	ft_split_free(links);
}

void	ft_read_data(int fd, t_array **arr)
{
	char	*temp;
	char	**split;
	int 	flag;

	ft_read_ants(fd, arr); //читает количество муравьёв
	flag = 0;
	while (get_next_line(fd, &temp))
	{
		if (temp[0] == '#') //если у нас одна "#" то мы пропускаем эту строчку
		{
			if (temp[1] == '#')
			{
				if (temp[2] == 's')
					flag = 1;   // флаг это костыль если флаг == 1 - то при создании комнаты мы её пометим как стартовую, если флаг == 2 - то при создании пометим как финишную
				else
					flag = 2;
			}
			free(temp);
			continue ;
		}
		split = ft_strsplit(temp, ' '); // если длина массива после сплита == 3 - то это комната, если 1 - то это связи
		free(temp);
		if (split[1] == NULL)
			ft_create_links(arr, split); //создаём линки в комнатах
		else
			ft_create_room(arr, split, &flag); //маллочим комнату, инициализируем переменные и закидываем её в общий массив всех комнат
		ft_split_free(split); //чистка памяти
	}
}