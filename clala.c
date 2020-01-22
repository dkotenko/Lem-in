#include "lem-in.h"
#include "libft/libft.h"

void	ft_paths_sort(t_paths *paths)
{
	int	i;
	i = -1;
	while(++i < paths->curr_path)
	{
		ft_path_sort(paths->path_arr[i]);
	}
}

void	ft_path_sort(t_path *path)
{
	int	temp[path->size];
	int i;
	int j;
	i = 0;
	j = path->size - 1;
	while (i < path->size)
	{
		temp[i] = path->path[j];
		j--;
		i++;
	}
	i = 0;
	while (i < path->size)
	{
		path->path[i] = temp[i];
		i++;
	}
}

t_paths *create_t_paths()
{
	t_paths *new;

	new = (t_paths *)malloc(sizeof(t_paths));
	new->curr_path = 0;
	new->path_arr = (t_path **)malloc(sizeof(t_path *) * 1000);
	return (new);
}

int		*copy_int_array(int *arr, int size)
{
	//need size_t instead of size OR NOT?!?!?!?!??!?!?!
	int i;
	int *new;

	new = (int *)malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		new[i] = arr[i];
		i++;
	}
	return (new);
}

t_path *copy_t_path(t_path *path)
{
	t_path *new;

	new = (t_path *)malloc(sizeof(t_path));
	new->size = path->size;
	new->path = copy_int_array(path->path, path->size);
	new->curr_size = path->curr_size;
	new->order = path->order;
	return (new);
}

t_paths *copy_t_paths(t_paths *paths)
{
	int		i;
	t_paths	*new;

	new = (t_paths *)malloc(sizeof(t_paths));
	new->curr_path = paths->curr_path;
	new->paths_lim = paths->paths_lim;
	new->time = paths->time;
	new->path_arr = (t_path **)malloc(sizeof(t_path *) * paths->curr_path);
	i = 0;
	while (i < paths->curr_path)
	{
		new->path_arr[i] = copy_t_path(paths->path_arr[i]);
		i++;
	}
	return (new);
}

t_array *get_copy_t_array(t_array *arr)
{
	int i;
	t_array *arr_copy;

	arr_copy = (t_array *)malloc(sizeof(t_array));
	arr_copy->max = arr->max;
	arr_copy->current = arr->current;
	arr_copy->start = arr->start;
	arr_copy->finish = arr->finish;
	arr_copy->ants = arr->ants;
	arr_copy->rooms = (t_room **)malloc(sizeof(t_room *) * arr->max);

	i = 0;
	while (i < arr->max)
	{
		arr_copy->rooms[i] = NULL;
		i++;
	}
	return (arr_copy);
}

t_room *copy_room_mod(t_room **rooms, int i)
{
	t_room	*room;

	room = (t_room*)malloc(sizeof(t_room));
	if (rooms[i]->s_lnk.is_copy)
		i = rooms[i]->s_lnk.room_copy;
	room->name = rooms[i]->name;
	room->s_lnk.links = (int *) malloc(sizeof(int) * (rooms[i]->s_lnk.cur_size));
	room->s_lnk.weights = (int *) malloc(sizeof(int) * (rooms[i]->s_lnk.cur_size));
	ft_fill_mem(room->s_lnk.links, rooms[i]->s_lnk.cur_size, -1);
	room->s_lnk.order = rooms[i]->s_lnk.order;
	room->s_lnk.room_copy = -1;
	room->s_lnk.is_copy = 0;
	room->s_lnk.max_size = rooms[i]->s_lnk.cur_size;
	room->s_lnk.cur_size = 0;
	return (room);
}

int 	room_in_no_expanded(t_array *arr_not_expanded, t_room *room)
{
	int		i;

	i = 0;
	while (i < arr_not_expanded->max)
	{
		if (arr_not_expanded->rooms[i])
		{
			; //printf("%s %s %d\n", room->name, arr_not_expanded->rooms[i]->name, i);
		}
		if (arr_not_expanded->rooms[i] && !ft_strcmp(room->name, arr_not_expanded->rooms[i]->name))
			return (1);
		i++;
	}
	return (0);
}

int     get_origin_room(int room_nb, t_array *arr)
{
	if (arr->rooms[room_nb]->s_lnk.is_copy)
		return (arr->rooms[room_nb]->s_lnk.room_copy);
	return (room_nb);
}

int     nbr_in_array_pos(int number, int *arr, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (arr[i] == number)
			return (i);
		i++;
	}
	return (-1);
}

int     nbr_in_links_pos(t_array *arr , int curr, int link)
{
	int link_index;
	int i;

	link_index = arr->rooms[curr]->s_lnk.links[link];
	i = 0;
	while (i < arr->rooms[link_index]->s_lnk.cur_size)
	{
		if (arr->rooms[link_index]->s_lnk.links[i] == curr)
			return (i);
		i++;
	}
	return (-1);
}

void	add_path_to_no_expanded(t_array *arr_not_expanded, t_array *arr, t_path *path)
{
	int i;
	int k;
	//int orig;

	i = path->size;
	while (--i > -1)
	{
		k = get_origin_room(path->path[i], arr);
		if (!room_in_no_expanded(arr_not_expanded, arr->rooms[k]))
		{
			arr_not_expanded->rooms[k] = copy_room_mod(arr->rooms, k);
			//arr_not_expanded->current++;
		}
		//orig = i > 0 ? get_origin_room(path->path[i - 1], arr) : 0;
		if (i > 0) /*&& nbr_in_links_pos(arr_not_expanded,	orig,
		arr_not_expanded->rooms[k]->s_lnk.links[arr_not_expanded->rooms[k]->s_lnk.cur_size])
			== -1)*/
		{
			arr_not_expanded->rooms[k]->s_lnk.links[arr_not_expanded->rooms[k]->s_lnk.cur_size] = \
			get_origin_room(path->path[i - 1], arr);
			arr_not_expanded->rooms[k]->s_lnk.weights[arr_not_expanded->rooms[k]->s_lnk.cur_size] = 1;
			arr_not_expanded->rooms[k]->s_lnk.cur_size++;
		}
	}
}

void	delete_double_links(t_array *arr)
{
	int i;
	int j;
	int pos_i_in_links_j;
	int pos_j_in_rooms;

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
			if (pos_i_in_links_j != -1)
			{
				arr->rooms[pos_j_in_rooms]->s_lnk.weights[pos_i_in_links_j] = -2;
				arr->rooms[i]->s_lnk.weights[j] = -2;
			}
		}
	}
}

void	delete_edges_bf(t_array *arr, t_path *path, t_deleted_edges *edges)
{
	int 	index_first;
	int 	i;

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

t_deleted_edges	*create_deleted_edges(int size)
{
	t_deleted_edges *deleted_edges;

	deleted_edges = (t_deleted_edges *)malloc(sizeof(deleted_edges)	* size);
	deleted_edges->edge_indexes = (int *)malloc(sizeof(int)	* size);
	deleted_edges->edge_rooms = (int *)malloc(sizeof(int) * size);
	deleted_edges->curr_size = 0;
	deleted_edges->size = size;
	return (deleted_edges);
}

void	restore_edges_bf(t_array *arr, t_deleted_edges *edges)
{
	int i;

	i = -1;
	while (++i < edges->curr_size)
	{
		arr->rooms[edges->edge_rooms[i]]->s_lnk.weights[edges->edge_indexes[i]] = 1;
	}
}

void	free_t_path(t_path **path)
{
	free((*path)->path);
	free(*path);
}

void	free_t_deleted_edges(t_deleted_edges **edges)
{
	free((*edges)->edge_indexes);
	free((*edges)->edge_rooms);
	free(*edges);
}

void	handle_paths(t_array *arr_not_expanded, t_array *arr, t_paths *paths)
{
	int i;
	t_path *tmp;
	t_deleted_edges *deleted_edges;

	add_path_to_no_expanded(arr_not_expanded, arr, paths->path_arr[paths->curr_path - 1]);

	delete_double_links(arr_not_expanded);
	deleted_edges = create_deleted_edges(arr_not_expanded->current);
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
		free_t_path(&tmp);

	}
	if (deleted_edges->curr_size)
	{
		restore_edges_bf(arr_not_expanded, deleted_edges);
	}

	free_t_deleted_edges(&deleted_edges);
}

void	ft_reader(int argc, char **argv, t_array **arr)
{
	int fd;

	*arr = NULL;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	ft_read_data(fd, arr); //читаем входные данные
}

int		ft_free(void *val)
{
	free(val);
	return (1);
}

/*
int			hash_table_add(int hash, int pointer, int *hash_table)
{
	int		i;


	i = 0;
	while (i + hash < hash_table.size)
	{
		if (hash_table[hash + i] == -1)
		{
			hash_table[hash] = pointer;
			return (1);
		}
		else if (hash_table[hash + i] == pointer)
			return (0);
		i++;
	}
	return (1);
}
*/

int		hash_func(char *s, int table_size)
{
	int		i;
	int		hash;
	int		len;

	hash = 0;
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		hash = ((hash * PRIME_NUMBER) + s[i]) % table_size;
		i++;
	}
	return (hash % table_size);
}

int		ft_path_limit(t_array *arr)
{
	int min;

	min = INT_MAX;
	if (min > arr->rooms[arr->start]->s_lnk.cur_size)
		min = arr->rooms[arr->start]->s_lnk.cur_size;
	if (min > arr->rooms[arr->finish]->s_lnk.cur_size)
		min = arr->rooms[arr->finish]->s_lnk.cur_size;
	if (min > arr->ants)
		min = arr->ants;
	return (min);
}