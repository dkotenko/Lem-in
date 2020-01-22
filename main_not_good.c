#include "lem-in.h"
#include "libft/libft.h"

int debug = 0;
int iter = 0;


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

void	ft_paths_sort(t_paths *paths)
{
	int	i;
	i = -1;
	while(++i < paths->curr_path)
	{
		ft_path_sort(paths->path_arr[i]);
	}
}

void	print_t_links(t_links *s_lnk, t_array *arr)
{
	int i;
	int printed;

	i = -1;
	printed = 0;
	while (++i < s_lnk->cur_size)
	{
//		if (s_lnk->weights[i] == -2)
//			continue;
		ft_putstr(": ");
		ft_putstr("lnk [");
		ft_putstr(arr->rooms[s_lnk->links[i]]->name);
		ft_putstr(",");
		ft_putnbr(s_lnk->weights[i]);
		ft_putstr("]");
		if (i < s_lnk->cur_size - 1)
			ft_putstr(" | ");
		printed++;
	}
	if (!printed)
		ft_putstr(" :no links, no weights");
	ft_putstr("\n");

}

void	print_t_array_rooms_with_links(t_array *arr)
{
	int i;

	i = -1;
//	printf("max: %d\n", arr->max);
//	printf("ants: %d\n", arr->ants);
//	printf("base: %d\n", arr->base);
//	printf("start: %d\n", arr->start);
//	printf("finish: %d\n", arr->finish);
//	printf("current: %d\n", arr->current);
	while(++i < arr->max)
	{
		if (!arr->rooms[i])
			continue ;
		ft_putstr("ROOM:");
		ft_putstr(arr->rooms[i]->name);
	//	printf(" lnkS:%d ", arr->rooms[i]->s_lnk.cur_size);
	//	printf(" lnkS:%d ", arr->rooms[i]->s_lnk.room_copy);
	//	printf("(%d)", arr->rooms[i]->s_lnk.order);
		print_t_links(&arr->rooms[i]->s_lnk, arr);
	}
}

void	print_t_path(t_path *path, t_array *arr)
{
	int i;

	i = -1;
	if (!path)
		ft_putstr("NO PATH\n");
	else
	{
		while (++i < path->size)
		{
			ft_putstr(arr->rooms[path->path[i]]->name);
			if (i < path->size - 1)
				ft_putstr("-");
		}
	}
	ft_putstr("\n");
}

void	print_t_paths(t_paths *paths, t_array *arr)
{
	int i;

	i = -1;
	while (++i < paths->curr_path)
		print_t_path(paths->path_arr[i], arr);
	ft_putstr("\n");
}

void	print_path(t_paths *paths, t_array *arr)
{
	// всё что ниже - печать в консоль данных
	int i = 0;
	int j = 0;
	printf("\n");
	//t_path *path = paths->path_arr[paths->curr_path - 1];

	while (j < paths->curr_path)
	{
		i = 0;
		while (paths->path_arr[j]->path[i] < paths->path_arr[j]->size)
		{
			printf("%s-", arr->rooms[paths->path_arr[j]->path[i]]->name);
			//printf("%d-", arr->rooms[paths->path_arr[j]->path[i]]->s_lnk.is_copy);
			i++;
		}
		printf("\n");
		j++;
	}
	i = 0;
	j = 0;
	while (i < arr->current)
	{
		printf("name: '%8s', links: ---> ", arr->rooms[i]->name);
		j = 0;
		while (j < arr->rooms[i]->s_lnk.cur_size)
		{
			if (arr->rooms[i]->s_lnk.weights[j] == -2)
			{
				j++;
				continue;
			}
			printf("|%d", arr->rooms[i]->s_lnk.links[j]);
			printf(" %+d|", arr->rooms[i]->s_lnk.weights[j]);
			j++;
		}
		//printf(" order: ---> %d", arr->rooms[i]->s_lnk.order);
		printf("\n");
		i++;
	}
	printf("\nstart: %d, finish: %d\n", arr->start, arr->finish);
	printf("ants: %d", arr->ants);
}

/*
 *
 *
 *
 *
 *
 */

void	ft_fill_mem(int *arr, int size, int num)
{
	int i;

	i = 0;
	while (i < size)
	{
		arr[i] = num;
		i++;
	}
}

void	curr_size_to_size(t_paths *paths)
{
	int i;

	i = -1;
	while (++i < paths->curr_path)
	{
		if (paths->path_arr[i])
			paths->path_arr[i]->curr_size = paths->path_arr[i]->size;
	}
}

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
	int			i;

	if (*arr == NULL)
	{
		*arr = (t_array*)malloc(sizeof(t_array) * 1);
		(*arr)->rooms = (t_room**)malloc(sizeof(t_room*) * size);
		(*arr)->max = size;
		(*arr)->current = 0;
		i = 0;
	}
	if ((*arr)->current == (*arr)->max)
	{
		size *= 2;
		(*arr)->rooms = ft_rooms_copy((*arr)->rooms, (*arr)->max);
		i = (*arr)->max;
		(*arr)->max *= 2;
	}
	while (i < size)
		(*arr)->rooms[i++] = NULL;
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
//	if(first_room == 2367 || second_room == 2367)
//	{
//
//		printf("first room: %d\n", first_room);
//		printf("second room: %d\n", second_room);
//	}
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

int		ft_find_room_bfs(t_room *rooms, int *i, int *j, t_path *path)
{
	while (*(j) < rooms->s_lnk.cur_size)
	{
		if (rooms->s_lnk.links[*j] == path->path[(*i)] && rooms->s_lnk.weights[*j] != -2)
			return (1);
		(*j)++;
	}
	return (0);
}

void	ft_check_for_cpy_bfs_smart(t_array **arr, t_path *path)
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

int		ft_find_best_room_bfs_smart(t_array **arr, int curr, int order)
{
	int i;
	int j;
	int best_room;
	//printf("[");
	i = 0;
	best_room = -1;
	while (i < (*arr)->current)
	{
		if ((*arr)->rooms[i]->s_lnk.order == order)
		{
			j = 0;
		//	printf("{%s}-", (*arr)->rooms[i]->name);
			while (j < (*arr)->rooms[i]->s_lnk.cur_size)
			{
				if ((*arr)->rooms[i]->s_lnk.weights[j] != -2 && (*arr)->rooms[i]->s_lnk.links[j] == curr)
				{
					if (best_room == -1)
						best_room = i;
					else if ((*arr)->rooms[i]->s_lnk.weights[j] == -1)
						best_room = i;
				}
				j++;
			}
		}
		i++;
	}
//	printf("]\n");
	return (best_room);
}

t_path	*ft_restore_path_bfs_smart(t_array **arr)
{
	t_path 	*path;
	int		order;
	int		i;
	int		best_room;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	path->path = (int*)malloc(sizeof(int) * ((*arr)->current + 1)); //!! ПОСЧИТАТЬ КОЛИЧЕСТВО ПАМЯТИ
	ft_fill_mem(path->path, (*arr)->current + 1, -1);
	i = 0;
	order = (*arr)->rooms[(*arr)->finish]->s_lnk.order - 1;
	path->size = (*arr)->rooms[(*arr)->finish]->s_lnk.order + 1;
	path->curr_size = path->size;
	path->path[0] = (*arr)->finish;
//	printf("order: %d, path[i]: %d\n", (*arr)->rooms[(*arr)->finish]->s_lnk.order, path->path[0]);
	while (i < (*arr)->rooms[(*arr)->finish]->s_lnk.order)
	{
//		printf("%s-%d(ord: %d)-", (*arr)->rooms[path->path[i]]->name,  path->path[i], order);
		best_room = ft_find_best_room_bfs_smart(arr, path->path[i], order);
		if (best_room == -1)
			best_room = ft_find_best_room_bfs_smart(arr, (*arr)->rooms[path->path[i]]->s_lnk.room_copy, order);
		path->path[i + 1] = best_room;
		i++;
		order--;
	}
//	printf("\n");
	i = 0;
//	printf("new path (%d) : ", path->size);
	while (i < path->size)
	{
//		printf("%s-", (*arr)->rooms[path->path[i]]->name);
//		printf("%d-", path->path[i]);
		i++;
	}
//	printf("\n");
	return (path);
}

t_path	*ft_restore_path_bfs(t_array **arr)
{
	t_path 	*path;
	int		j;
	int		k;
	int		i;
	int 	a;
	int 	is_room;

	is_room = 1;
	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	path->path = (int*)malloc(sizeof(int) * (*arr)->current - 1);
	ft_fill_mem(path->path, (*arr)->current - 1, -1);
	k = (*arr)->rooms[(*arr)->finish]->s_lnk.order;
	path->path[0] = (*arr)->finish;
	path->size = k + 1;
	path->curr_size = k + 1;
	path->order = 1;
	i = 0;
	while (k != 0)
	{
		j = 0;
		is_room = 0;
		while (j < (*arr)->rooms[path->path[i]]->s_lnk.cur_size)
		{
			if ((*arr)->rooms[(*arr)->rooms[path->path[i]]->s_lnk.links[j]]->s_lnk.order == k - 1)
			{
				is_room = 1;
				path->path[i + 1] = (*arr)->rooms[path->path[i]]->s_lnk.links[j];
				k--;
				i++;
				break;
			}
			j++;
		}
		if (is_room == 0)
		{
			a = 0;
			while (a < (*arr)->current)
			{
				if ((*arr)->rooms[a] && (*arr)->rooms[a]->s_lnk.order == k - 1)
				{
					j = 0;
					if (ft_find_room_bfs((*arr)->rooms[a], &i, &j, path) == 1)
					{
						path->path[i + 1] = a;
						k--;
						i++;
						is_room = 1;
						break;
					}
				}
				a++;
			}
		}
		if(is_room == 0)
			break;
	}
	i = 0;
//	printf("old path (%d) : ", path->size);
	while (i < path->size)
	{
//		printf("%s-", (*arr)->rooms[path->path[i]]->name);
		i++;
	}
//	printf("\n");
	return (path);
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
			(*arr)->rooms[i]->flag = -1;
		}
		i++;
	}
}

int		ft_find_recur_bfs(int *queue, int **cur_queue, t_array **arr)
{
	int		i;
	t_room	**rooms;
//!! flag == 1 - OUT, flag == 2 - IN
	rooms = (*arr)->rooms;
	i = 0;
	while (i < rooms[*queue]->s_lnk.cur_size)
	{


		if (rooms[rooms[*queue]->s_lnk.links[i]]->s_lnk.order == -1 && rooms[*queue]->s_lnk.weights[i] != -2)
		{
	//		printf("queue: %s, flag: %d, is_cpy: %d\n", rooms[*queue]->name, rooms[*queue]->flag, rooms[*queue]->s_lnk.room_copy);
			if (rooms[rooms[*queue]->s_lnk.links[i]]->s_lnk.room_copy != -1) //если вершина разделённая то ищем IN или OUT она
			{
				if (rooms[*queue]->s_lnk.weights[i] == 1 && rooms[rooms[*queue]->s_lnk.links[i]]->flag != 2)
					rooms[rooms[*queue]->s_lnk.links[i]]->flag = 2; //если пришли по положительному пути - это IN вершина
				if (rooms[*queue]->s_lnk.weights[i] == -1)
					rooms[rooms[*queue]->s_lnk.links[i]]->flag = 1; //если пришли по отрицательному пути - это OUT вершина
			}
			if ((rooms[*queue]->flag == -1) || (rooms[*queue]->flag == 2 && rooms[*queue]->s_lnk.weights[i] == -1) || (rooms[*queue]->flag == 1 && rooms[*queue]->s_lnk.weights[i] == 1))
		//		если текущая комната, что мы смотрим - не разделённая то просто пушим найденный линк в очередь || Или комната IN и вес отрицательный || или комната OUT и вес положительный
			{
				**cur_queue = rooms[*queue]->s_lnk.links[i];
				rooms[rooms[*queue]->s_lnk.links[i]]->s_lnk.order = rooms[*queue]->s_lnk.order + 1;
//				if (rooms[*queue]->s_lnk.room_copy != -1)
//					rooms[rooms[*queue]->s_lnk.room_copy]->s_lnk.order = rooms[*queue]->s_lnk.order;
				(*cur_queue)++;
				if (rooms[*queue]->s_lnk.links[i] == (*arr)->finish)
					return (1);
			}
		}
		i++;
	}
	return (0);
}

t_path	*ft_find_path_bfs(t_array **arr)
{
	int *queue;
	int *cur_queue;
	int i;
	int test;
	i = 0;
	int m = 100000;
	queue = (int*)malloc(sizeof(int) * m); //!!! НАДО ПОСЧИТАТЬ НОРМАЛЬНОЕ КОЛИЧЕСТВО ПАМЯТИ ДЛЯ МАЛЛОКА
	while (i < m)
	{
		queue[i] = -1;
		i++;
	}
	*queue = (*arr)->start;
	(*arr)->rooms[(*arr)->start]->s_lnk.order = 0;
	cur_queue = queue;
	cur_queue++;
	int j = 0;
	int *start = queue;
	while (*queue != -1)
	{
		j = 0;
		while (queue[j] != -1)
			j++;
		if ((test = ft_find_recur_bfs(queue, &cur_queue, arr)))
			break ;
		queue++;
	}
	//!!!!! не забыть почистить память
//	ft_restore_path_bfs(arr);
	while (*start != -1)
	{
//		printf("|%d-%d|", *start, (*arr)->rooms[*start]->s_lnk.order);
		start++;
	}
//	printf("\n");
//	print_t_array_rooms_with_links(*arr);
//	ft_restore_path_bfs(arr);
	return ft_restore_path_bfs_smart(arr);
}

void	ft_print_bf_matrix(int **matrix, int **path, t_array **arr)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < (*arr)->current - 1)
	{
		j = 0;
		while (j < (*arr)->current)
		{
			printf("%10d ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
	i = 0;
	j = 0;
	while (i < (*arr)->current - 1)
	{
		j = 0;
		while (j < (*arr)->current)
		{
			printf("%3d ", path[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void 	ft_malloc_bf_matrix(t_array **arr, int ***matrix, int ***path_mtrx)
{
	int i;

	i = 0;
	*matrix = (int**)malloc(sizeof(int*) * ((*arr)->current - 1));
	*path_mtrx = (int**)malloc(sizeof(int*) * ((*arr)->current - 1));
	while (i < (*arr)->current - 1)
	{
		(*matrix)[i] = (int*)malloc(sizeof(int) * (*arr)->current);
		(*path_mtrx)[i] = (int*)malloc(sizeof(int) * (*arr)->current);
		ft_fill_mem((*matrix)[i], (*arr)->current, INT_MAX);
		ft_fill_mem((*path_mtrx)[i], (*arr)->current, -1);
		i++;
	}

}

void 	ft_free_bf_matrix(t_array **arr, int **matrix, int **path_mtrx)
{
	int i;

	i = 0;
	while (i < (*arr)->current - 1)
	{
		free(matrix[i]);
		free(path_mtrx[i]);
		i++;
	}
	free(matrix);
	free(path_mtrx);
}

void	ft_fill_1st_line(t_array **arr, int **matrix, int **path)
{
	int k;

	k = 0;
	matrix[0][(*arr)->start] = 0;
	path[0][(*arr)->start] = (*arr)->start;
	while (k < (*arr)->rooms[(*arr)->start]->s_lnk.cur_size)
	{
		matrix[0][(*arr)->rooms[(*arr)->start]->s_lnk.links[k]] = (*arr)->rooms[(*arr)->start]->s_lnk.weights[k];
		path[0][(*arr)->rooms[(*arr)->start]->s_lnk.links[k]] = (*arr)->start;
		k++;
	}
}

void	ft_find_path_cycle(t_array **arr, int **matrix, int **path_mtrx, int i)
{
	int j;
	int k;

	j = 0;
	while (j < (*arr)->current)
	{
		if (matrix[i - 1][j] == INT_MAX && j++)
			continue;
		k = 0;
		matrix[i][j] = matrix[i - 1][j];
		path_mtrx[i][j] = path_mtrx[i - 1][j];
		while (k < (*arr)->rooms[j]->s_lnk.cur_size)
		{
			if ((*arr)->rooms[j]->s_lnk.weights[k] != -2)
				if (matrix[i][(*arr)->rooms[j]->s_lnk.links[k]] > matrix[i - 1][j] + 1)
				{
					matrix[i][(*arr)->rooms[j]->s_lnk.links[k]] = matrix[i - 1][j] + 1;
					path_mtrx[i][(*arr)->rooms[j]->s_lnk.links[k]] = j;
				}
			k++;
		}
		j++;
	}
}

t_path	*ft_restore_path_bf(t_array **arr, int **path_mtrx)
{
	t_path *path;
	int i;
	int j;
	int k;

	path = (t_path *)malloc(sizeof(t_path));
	path->path = (int*)malloc(sizeof(int) * (*arr)->current - 1);
	ft_fill_mem(path->path, (*arr)->current - 1, -1);
	i = (*arr)->current - 2;
	j = (*arr)->finish;
	k = 1;
	path->path[0] = (*arr)->finish;
	while (path_mtrx[i][j] != (*arr)->start && j != -1)
	{
		path->path[k] = path_mtrx[i][j];
		k++;
		j = path_mtrx[i][j];
		i--;
	}
	path->path[k] = (*arr)->start;
	path->order = 1;
	path->size = k + 1;
	path->curr_size = k + 1;
	return (j != -1 ? path : NULL);
}

t_path	*ft_find_path_bf(t_array **arr, int i)
{
	int	**matrix;
	int **path_mtrx;
	t_path	*path;

	ft_malloc_bf_matrix(arr, &matrix, &path_mtrx);
	ft_fill_1st_line(arr, matrix, path_mtrx);
	while (i < (*arr)->current - 1)
	{
		ft_find_path_cycle(arr, matrix, path_mtrx, i);
		i++;
	}
	path = ft_restore_path_bf(arr, path_mtrx);
	ft_free_bf_matrix(arr, matrix, path_mtrx);
	return (path);
}

void	ft_expand_graph(t_array **arr, int *path)
{
	int		i;
	int 	j;
	t_room	*room;
//printf("\n");
	i = 0;
	while (path[i] != -1)
	{
		j = 0;
//		printf("%d\n", path[i]);
		// reverse path -->
	//	printf("name: %s: lnk: ", (*arr)->rooms[path[i]]->name);
		while (j < (*arr)->rooms[path[i]]->s_lnk.cur_size)
		{
//			printf("%s-", (*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.links[j]]->name);
			if (i != 0 && (*arr)->rooms[path[i]]->s_lnk.links[j] == path[i - 1])
				(*arr)->rooms[path[i]]->s_lnk.weights[j] = -2; // -2 - это стёртые пути
			if ((*arr)->rooms[path[i]]->s_lnk.links[j] == path[i + 1] && ((*arr)->rooms[path[i]]->s_lnk.room_copy == -1 && (*arr)->rooms[path[i + 1]]->s_lnk.room_copy == -1))
				(*arr)->rooms[path[i]]->s_lnk.weights[j] = -1; // -1 - это реверснутые пути
			j++;
		}
//		printf("\n");
		// <-- reverse path
		i++;
	}
	i = 0;

	while (path[i] != -1)
	{
		// --> duplicate room
	//		printf("name: %s\n", (*arr)->rooms[path[i]]->name);
		if (i != 0 && path[i + 1] != -1 && (*arr)->rooms[path[i]]->s_lnk.room_copy == -1)
		{
			room = (t_room*)malloc(sizeof(t_room));
			ft_cpy_room_data(room, (*arr)->rooms[path[i]], (*arr)->current, path[i]);
			ft_arr_push(arr, room);

		}

		// <-- duplicate room
		i++;
	}

	i = 0;
	while (path[i + 1] != -1)
	{
		j = 0;
		while (j < (*arr)->rooms[path[i]]->s_lnk.cur_size)
		{
			// --> замена исходящих ссылок в (IN) и FINISH на новые (OUT) следующие по порядку в пути
			if ((*arr)->rooms[path[i]]->s_lnk.links[j] == path[i + 1] && path[i + 1] != (*arr)->start)
				(*arr)->rooms[path[i]]->s_lnk.links[j] = (*arr)->rooms[path[i + 1]]->s_lnk.room_copy;
			// <-- замена исходящих ссылок в (IN) и FINISH на новые (OUT) следующие по порядку в пути

			// --> стирание исходящих ссылок в вершине IN кроме ссылки на прошлую вершину пути
			if (i != 0 && (*arr)->rooms[path[i]]->s_lnk.weights[j] == 1)
				(*arr)->rooms[path[i]]->s_lnk.weights[j] = -2;
			// <-- стирание исходящих ссылок в вершине IN кроме ссылки на прошлую вершину пути

			// --> стирание исходящей ссылки в вершине OUT на прошлую вершину IN в пути
			if (i != 0 && (*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.weights[j] == -1  && ((*arr)->rooms[path[i]]->s_lnk.room_copy > (*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.room_copy))
				(*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.weights[j] = -2;
			// <-- стирание исходящей ссылки в вершине OUT на прошлую вершину IN в пути
			j++;
		}
		// --> добавление связи между OUT и IN
		if ((*arr)->rooms[path[i]]->s_lnk.room_copy != -1 && ((*arr)->rooms[path[i]]->s_lnk.room_copy > (*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.room_copy))
			ft_links_push(&((*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk), path[i], 0);
		// <-- добавление связи между OUT и IN
		i++;
	}

	i = 0;
	j = 0;
	while (i < (*arr)->current)
	{
		j = 0;
		//	printf("name: %s:", (*arr)->rooms[i]->name);
		while (j < (*arr)->rooms[i]->s_lnk.cur_size)
		{
//			printf("lnk:%s-%d w:%d   ", (*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->name ,(*arr)->rooms[i]->s_lnk.links[j], (*arr)->rooms[i]->s_lnk.weights[j]);
			j++;
		}
//		printf("\n");
		i++;
	}

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

int		ft_calc_path_time(t_array **arr, t_paths *paths)
{
	int i;
	int j;
	int min_path;
	int min_path_num;
	int max_time;

	i = 0;
	max_time = 0;
	curr_size_to_size(paths);
	while (i < (*arr)->ants)
	{
		j = 0;
		min_path = 1000000;
		while (j < paths->curr_path)
		{
			if (paths->path_arr[j]->curr_size - 1 < min_path)
			{
				min_path = paths->path_arr[j]->curr_size - 1;
				min_path_num = j;
			}
			j++;
		}
		paths->path_arr[min_path_num]->curr_size += 1;
		if (max_time < paths->path_arr[min_path_num]->curr_size - 1)
			max_time = paths->path_arr[min_path_num]->curr_size - 1;
		i++;
	}
	max_time--;
//	printf("time: %d\n", max_time);
	return (max_time);
}

t_ant	*ft_ants_creator(int start_room)
{
	static int	num = 1;
	char		let[2];
	char 		*numb;
	t_ant		*clone;

	let[0] = start_room;
	let[0] = 'L';
	let[1] = '\0';
	numb = ft_itoa(num);
	clone = (t_ant*)malloc(sizeof(t_ant));
	clone->name = ft_strjoin(let, numb);
	num++;
	clone->position = 0;
	clone->order = -1;
	clone->path = -1;
	clone->next = NULL;
	free(numb);
	return (clone);
}

void	ft_ant_reporting(char *name, char *room)
{
	printf("%s-%s ", name, room);
}

void	ft_ants_parade(t_array **arr, t_ant *ants, t_paths *paths)
{
	t_ant	*first_ant;
	int		order;
	int 	is_all_finished;

	order = 0;
	first_ant = ants;
	is_all_finished = 0;
	ft_paths_sort(paths);
	printf("\n");
	while (!is_all_finished)
	{
		is_all_finished = 1;
		ants = first_ant;
		while (ants->next != NULL)
		{
			if (ants->order == order && ants->position < paths->path_arr[ants->path]->size - 1)
			{
				ants->position += 1;
				ants->order += 1;
				ft_ant_reporting(ants->name, (*arr)->rooms[paths->path_arr[ants->path]->path[ants->position]]->name);
				is_all_finished = 0;
			}
			ants = ants->next;
		}
		order++;
		if (!is_all_finished)
			printf("\n");
	}
}

void	ft_list_sort(t_ant *ants)
{
	t_ant	*start;
	int 	path;
	int 	order;

	start = ants;
	while (ants->next != NULL)
	{
		if (ants->order > ants->next->order && ants->next->next != NULL)
		{
			order = ants->order;
			path = ants->path;
			ants->order = ants->next->order;
			ants->path = ants->next->path;
			ants->next->order = order;
			ants->next->path = path;
			ants = start;
			continue;
		}
		ants = ants->next;
	}
}

void 	ft_print_t_paths(t_paths *paths)
{
	int i = 0;
	int j = 0;

	while (i < paths->curr_path)
	{
		printf("i is: %d - [", i);
		j = 0;

		while (j < paths->path_arr[i]->size)
		{
			printf("%d-", paths->path_arr[i]->path[j]);
			j++;
		}
		printf("]\n");
		i++;
	}
}

void	ft_ants_prepare_to_parade(t_array **arr, t_paths *paths)
{
	t_ant	*ants;
	t_ant	*first_ant;
	int 	i;
	int		j;
	int 	min_path;
	int 	min_path_num;

	curr_size_to_size(paths);
	ants = ft_ants_creator((*arr)->start);
	first_ant = ants;
	i = 0;
//	printf("%d\n", (*arr)->ants);
	while (i < (*arr)->ants)
	{
		j = 0;
		min_path = 1000000;
		while (j < paths->curr_path)
		{
			if (paths->path_arr[j]->curr_size < min_path)
			{
				min_path = paths->path_arr[j]->curr_size;
				min_path_num = j;
			}
			j++;
		}
		paths->path_arr[min_path_num]->curr_size += 1;
		ants->path = min_path_num;
		ants->order = paths->path_arr[min_path_num]->order;
		paths->path_arr[min_path_num]->order += 1;
		ants->next = ft_ants_creator((*arr)->start); // !!!! создаётся на 1 муравья больше чем надо и это ок
		ants = ants->next;
		i++;
	}
	ants = first_ant;
	while (ants->next != NULL)
	{
	//	printf("name: %s, p:%d, o:%d\n", ants->name, ants->path, ants->order);
		ants = ants->next;
	}
	ants = first_ant;
	ft_list_sort(ants);
	ft_ants_parade(arr, ants, paths);
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

t_path	*ft_find_path_dfs(t_array **arr)
{
	t_path		*result;
	static int	i = -1;
	int			j;
	int			k;
//	printf("size: %d\n", (*arr)->rooms[(*arr)->start]->s_lnk.cur_size);
//	print_t_array_rooms_with_links(*arr);
//	printf("\n");

	if (i == -1)
		i = (*arr)->rooms[(*arr)->start]->s_lnk.cur_size - 1;
	result = (t_path *)malloc(sizeof(t_path));
	result->path = (int*)malloc(sizeof(int) * (*arr)->current - 1);
	ft_fill_mem(result->path, (*arr)->current - 1, -1);
	result->path[0] = (*arr)->start;
	result->path[1] = (*arr)->rooms[(*arr)->start]->s_lnk.links[i];
	j = 1;
	while (result->path[j] != (*arr)->finish)
	{
		k = 0;
		while (k < (*arr)->rooms[result->path[j]]->s_lnk.cur_size)
		{
			if ((*arr)->rooms[result->path[j]]->s_lnk.weights[k] != -2)
			{
				j++;
				result->path[j] = (*arr)->rooms[result->path[j - 1]]->s_lnk.links[k];
				break;
			}
			k++;
		}
	}
	result->size = 0;
	while (result->path[result->size] != (*arr)->finish)
		result->size++;
	result->size++;
	result->curr_size = result->size;
	result->order = 1;
	i--;
	ft_path_sort(result);
	return (result);
}

int		ft_find_first_room(t_array **arr, int i)
{
	int j;
	int result;

	j = 0;
	result = 0;
	while (j < (*arr)->rooms[(*arr)->start]->s_lnk.cur_size)
	{
		if ((*arr)->rooms[(*arr)->start]->s_lnk.weights[j] == -2)
			result++;
		if (result == i - 1)
			return (result);
		j++;
	}
	printf("Error in ft_find_first_room!");
	exit(5);
	return (0);
}

t_path	*ft_find_path_dfs_rev(t_array **arr)
{
	t_path		*result;
	static int	i = 0;
	int			j;
	int			k;
//	int 		a;

	j = 0;
//	print_t_array_rooms_with_links(*arr);
	while (i < (*arr)->rooms[(*arr)->start]->s_lnk.cur_size)
	{
//		printf("i in arr is: %d\n", i);
		if ((*arr)->rooms[(*arr)->start]->s_lnk.weights[i] == -2)
			break;
		i++;
	}
//	printf("i after arr is: %d\n", i);
	j = 0;
//	a = ft_find_first_room(arr, i);
//	printf("i is: %d\n",i);
	result = (t_path *)malloc(sizeof(t_path));
	result->path = (int*)malloc(sizeof(int) * (*arr)->current - 1);
	ft_fill_mem(result->path, (*arr)->current - 1, -1);
	result->path[0] = (*arr)->start;
	result->path[1] = (*arr)->rooms[(*arr)->start]->s_lnk.links[i];
//	printf("res.path[1]: %d\n", result->path[1]);
	j = 1;
	while (result->path[j] != (*arr)->finish)
	{
		k = 0;
//		printf("CHECK\n");
		while (k < (*arr)->rooms[result->path[j]]->s_lnk.cur_size)
		{
			if ((*arr)->rooms[result->path[j]]->s_lnk.weights[k] == -2)
			{
			//	printf("|%d|", result->path[j]);
				j++;
				result->path[j] = (*arr)->rooms[result->path[j - 1]]->s_lnk.links[k];
				break;
			}
			k++;
		}
	}
	result->size = 0;
	while (result->path[result->size] != (*arr)->finish)
		result->size++;
	result->size++;
	result->curr_size = result->size;
	result->order = 1;
	//i--;
	j = 0;
//	printf("rev path: ");
	while (j < result->size)
	{
//		printf("%d-", result->path[j]);
		j++;
	}
//	printf("CHECK\n");
//	printf("\n");
//	print_t_array_rooms_with_links(*arr);
	i++;
	if (i == (*arr)->rooms[(*arr)->start]->s_lnk.cur_size)
		i = 0;

	//ft_path_sort(result);
	return (result);
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

#define PRIME_NUMBER 17
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

void	ft_modify_gpaph(t_array **arr, t_path *path_struct)
{
	int i;
	int j;
	int *path;

	i = 0;
	path = path_struct->path;

//	printf("before modify. size: %d | ", path_struct->size);
//	while (i < path_struct->size)
//	{
//		printf("%s-", (*arr)->rooms[path[i]]->name);
//		i++;
//	}
//	printf("\n");

	i = -1;
	while (++i < path_struct->size)
	{
//		printf("i: %d, size: %d\n", i, path_struct->size);
		j = 0;
		while (j < (*arr)->rooms[path[i]]->s_lnk.cur_size)
		{
			if (i != 0 && (*arr)->rooms[path[i]]->s_lnk.links[j] == path[i - 1])
			{
	//			printf("-name1:%s,cpy:%d | name2:%s,cpy:%d\n",(*arr)->rooms[path[i]]->name,(*arr)->rooms[path[i]]->s_lnk.room_copy,(*arr)->rooms[path[i - 1]]->name, (*arr)->rooms[path[i - 1]]->s_lnk.room_copy);
//				if ((*arr)->rooms[path[i]]->s_lnk.room_copy == -1 || (*arr)->rooms[path[i - 1]]->s_lnk.room_copy == -1)
				if ((*arr)->rooms[path[i]]->s_lnk.weights[j] == 1)
					(*arr)->rooms[path[i]]->s_lnk.weights[j] = -2;
				else
					(*arr)->rooms[path[i]]->s_lnk.weights[j] = 1;
			}
			if ((*arr)->rooms[path[i]]->s_lnk.links[j] == path[i + 1])
			{
	//			printf("+name1:%s,cpy:%d | name2:%s,cpy:%d\n",(*arr)->rooms[path[i]]->name,(*arr)->rooms[path[i]]->s_lnk.room_copy,(*arr)->rooms[path[i + 1]]->name, (*arr)->rooms[path[i + 1]]->s_lnk.room_copy);
//				if ((*arr)->rooms[path[i]]->s_lnk.room_copy == -1 || (*arr)->rooms[path[i + 1]]->s_lnk.room_copy == -1)
				if ((*arr)->rooms[path[i]]->s_lnk.weights[j] == 1)
					(*arr)->rooms[path[i]]->s_lnk.weights[j] = -1;
				else
					(*arr)->rooms[path[i]]->s_lnk.weights[j] = 1;
			}
			j++;
		}
//		i++;
	}
	i = 0;
//	print_t_array_rooms_with_links(*arr);
//	print_t_array_rooms_with_links(*arr);
//	path = start;
	while (path[i] != -1)
	{
		(*arr)->rooms[path[i]]->s_lnk.room_copy = 1;
		i++;
	}
//	printf("\n");

}

t_paths *ft_path_cycle(t_array **arr)
{
	int i;
	t_paths *result;

	i = 0;
	result = create_t_paths();
	result->curr_path = 0;
	while (i < (*arr)->rooms[(*arr)->start]->s_lnk.cur_size)
	{
		if ((*arr)->rooms[(*arr)->start]->s_lnk.weights[i] == -2)
			result->curr_path += 1;
		i++;
	}
	i = 0;
	while (i < result->curr_path)
	{
		result->path_arr[i] = ft_find_path_dfs_rev(arr);
		i++;
	}
	print_t_paths(result, *arr);
	return (result);
}

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

int    main(int argc, char **argv)
{
	t_array	*arr;
	//t_array	*arr_not_expanded;
	t_paths	*paths;
	t_paths	*prev;
	//t_array *test;
	int i = 0;
	int a = 0;
	int 	path_counter;
	int path_limit;

	ft_reader(argc, argv, &arr);
	paths = create_t_paths();
	//arr_not_expanded = get_copy_t_array(arr);
	path_counter = 0;
	path_limit = ft_path_limit(arr);
	arr->base = arr->current;
	//test = ft_cpy_graph(arr);
//	print_t_array_rooms_with_links(arr);
//	print_t_array_rooms_with_links(test);
//	return (0);
//	print_t_array_rooms_with_links(arr);
	while (path_counter < path_limit)
	{
		if (path_counter)
			prev = copy_t_paths(paths);
		i = 0;
		while (i < paths->curr_path)
		{

//			ft_expand_graph(&arr, paths->path_arr[i]->path);
			i++;
		}

		paths->path_arr[paths->curr_path] = ft_find_path_bfs(&arr);
		ft_clear_order(&arr);

//		printf("\n");
		ft_modify_gpaph(&arr,  paths->path_arr[paths->curr_path]);
//		print_t_paths(paths, arr);
//		print_t_array_rooms_with_links(arr);
//

		ft_check_for_cpy_bfs_smart(&arr, paths->path_arr[paths->curr_path]);

//		print_t_array_rooms_with_links(arr);
		if (!paths->path_arr[paths->curr_path])
			break;
		paths->curr_path++;
		i = 0;
		paths = ft_path_cycle(&arr);
		a = 0;
		paths->curr_path = 0;

		while (a < arr->rooms[arr->start]->s_lnk.cur_size)
		{
			if (arr->rooms[arr->start]->s_lnk.weights[a] == -2)
				paths->curr_path++;
			a++;

		}

		while (i < paths->curr_path)
		{
			paths->path_arr[paths->curr_path] = ft_find_path_dfs_rev(&arr);
			i++;

		}

//		handle_paths(arr_not_expanded, arr, paths);

		paths->time = ft_calc_path_time(&arr, paths);
//		print_t_array_rooms_with_links(arr);
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
//		arr = ft_cpy_graph(test);
		path_counter++;
		i = 0;
//		printf("path counter: %d\n", path_counter);
//		while (i < path_counter)
//		{
//
//			print_t_path(paths->path_arr[i], arr);
//			i++;
//		}

	}
//	arr = ft_cpy_graph(test);
	i = 0;
//	printf("------");
//	while (i < paths->curr_path)
//	{
//		print_t_path(paths->path_arr[i], arr);
//	//	ft_expand_graph(&arr, paths->path_arr[i]->path);
//	//	print_t_array_rooms_with_links(arr);
//		i++;
//	}
	
	ft_ants_prepare_to_parade(&arr, paths);
//	print_t_paths(a1, arr);
//	print_t_array_rooms_with_links(arr);
//	ft_find_path_dfs_rev(&arr);
//	ft_find_path_dfs_rev(&arr);
//	ft_find_path_dfs_rev(&arr);
//	printf("time: %d\n", paths->time);
	return (0);
}