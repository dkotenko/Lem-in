#include "lem-in.h"
#include "libft/libft.h"

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

	if (*arr == NULL)
	{
		*arr = (t_array*)malloc(sizeof(t_array) * 1);
		(*arr)->rooms = (t_room**)malloc(sizeof(t_room*) * size);
		(*arr)->max = size;
		(*arr)->current = 0;
		return ;
	}
	if ((*arr)->current == (*arr)->max)
	{
		size *= 2;
		(*arr)->rooms = ft_rooms_copy((*arr)->rooms, (*arr)->max);
		(*arr)->max *= 2;
		//printf("%s\n", (*arr)->rooms[1]->name);
		return ;
	}
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
	if (s_lnk->links == NULL) //если у комнаты ещё нет линков то маллочим их
	{
		s_lnk->links = (int*)malloc(sizeof(int) * s_lnk->max_size);
		s_lnk->weights = (int*)malloc(sizeof(int) * s_lnk->max_size);
	}
	else if (s_lnk->cur_size == s_lnk->max_size) //если линков уже столько же сколько выделено памяти, то делаем перемаллок
	{
		s_lnk->max_size *= 2;
		s_lnk->links = ft_int_arr_realloc(s_lnk->links, s_lnk->max_size);
		s_lnk->weights = ft_int_arr_realloc(s_lnk->weights, s_lnk->max_size);
	}
	s_lnk->links[s_lnk->cur_size] = push; //добавляем линк в структуру
	s_lnk->weights[s_lnk->cur_size] = weight; //добавляем вес линка в структуру
//	printf("%d ", s_lnk->links[s_lnk->cur_size]);
//	printf("%d ", s_lnk->weights[s_lnk->cur_size]);
	(s_lnk->cur_size)++; //увеличиваем количество линков
}

void	ft_arr_push(t_array **arr, t_room *room)
{
	if (*arr == NULL || (*arr)->current == (*arr)->max)  //если ещё нет ниодной комнаты - то маллочим весь массив
		ft_arr_malloc(arr);
	(*arr)->rooms[(*arr)->current] = room; //добавляем комнату в массив
//	printf("%s %d %d\n", (*arr)->rooms[(*arr)->current]->name, (*arr)->current, (*arr)->max);
	(*arr)->current++; //увеличиваем счётчик комнат в массиве
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
	room->s_lnk.cur_size = 0;
	room->s_lnk.max_size = ARR_INIT_SIZE;
	room->s_lnk.order = -1;
	room->s_lnk.room_copy = -1;
	room->s_lnk.links = NULL;
	room->s_lnk.is_copy = 0;
	ft_arr_push(arr, room); //закидываем комнату в общий массив
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
	while (i < (*arr)->current) //бежим по всему массиву комнат и ищем обе комнаты по именам связей. Запоминаем их индекс в массиве
	{
		if (!(ft_strcmp(links[0], (*arr)->rooms[i]->name)))
			first_room = i;
		if (!(ft_strcmp(links[1], (*arr)->rooms[i]->name)))
			second_room = i;
		i++;
	}
//	printf("%s ", (*arr)->rooms[first_room]->name);
//	printf("%s ", (*arr)->rooms[second_room]->name);
	ft_links_push(&((*arr)->rooms[first_room]->s_lnk), second_room, 1); //к первой комнате добавляем связь со второй
	ft_links_push(&((*arr)->rooms[second_room]->s_lnk), first_room, 1); //к второй комнате добавляем связь с первой
//	printf("%d ", (*arr)->rooms[first_room]->s_lnk.links[(*arr)->rooms[first_room]->s_lnk.cur_size]);
//	printf("%d\n", (*arr)->rooms[second_room]->s_lnk.links[(*arr)->rooms[second_room]->s_lnk.cur_size]);
//	printf("\n");
//	printf("%d \n", (*arr)->rooms[first_room]->s_lnk.links[0]);
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

int		ft_find_recur(int *queue, int **cur_queue, t_array **arr)
{
	int		i;
	t_room	**rooms;

	rooms = (*arr)->rooms;
	i = 0;
	while (i < rooms[*queue]->s_lnk.cur_size)
	{
		if (rooms[rooms[*queue]->s_lnk.links[i]]->s_lnk.order == -1)
		{
			**cur_queue = rooms[*queue]->s_lnk.links[i];
			rooms[rooms[*queue]->s_lnk.links[i]]->s_lnk.order = rooms[*queue]->s_lnk.order;
			rooms[rooms[*queue]->s_lnk.links[i]]->s_lnk.order += 1;
			printf("|%s:%d|", rooms[rooms[*queue]->s_lnk.links[i]]->name, rooms[rooms[*queue]->s_lnk.links[i]]->s_lnk.order);
			(*cur_queue)++;
			if (rooms[*queue]->s_lnk.links[i] == (*arr)->finish)
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_find_path(t_array **arr)
{
	int *queue;
	int *cur_queue;
	int i;

	i = 0;
	queue = (int*)malloc(sizeof(int) * 1000);
	while (i < 1000)
	{
		queue[i] = -1;
		i++;
	}
	*queue = (*arr)->start;
	(*arr)->rooms[(*arr)->start]->s_lnk.order = 0;
	cur_queue = queue;
	cur_queue++;
	int j = 0;
	while (*queue != -1)
	{
		j = 0;
		printf("\n");
		printf("---> queue:");
		while (queue[j] != -1)
		{
			printf("%d ", queue[j]);
			j++;
		}
		if (ft_find_recur(queue, &cur_queue, arr))
			break ;
		queue++;
	}
}

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
	*matrix = (int**)malloc(sizeof(int*) * (*arr)->current - 1);
	*path_mtrx = (int**)malloc(sizeof(int*) * (*arr)->current - 1);
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

t_path		*ft_restore_path(t_array **arr, int **path_mtrx)
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
		//printf("%d\n", path[k - 1]);
		path->path[k] = path_mtrx[i][j];
		k++;
		j = path_mtrx[i][j];
		i--;
	}
	path->path[k] = (*arr)->start;
	path->size = k + 1;
//	while (*path != -1)
//	{
//		printf("%d ", *path);
//		path++;
//	}
	return (j != -1 ? path : NULL);
}

t_path		*ft_find_path_bf(t_array **arr, int i, int j, int k)
{
	int	**matrix; //беллман форд работает через матрицу.
	// Посмотри видос с названием "M46 Bellman Ford Algm single source" на ютубе.
	// Длина видоса 15.44. Смотреть с 6.00 по 11.30 минуты

	int **path_mtrx; //сюда я записываю индексы комнат, чтобы потом по ним восстановить путь (про это в видосе не говорится)
	t_path	*path; //это итоговый путь который возвращает функция (массив интов)

	ft_malloc_bf_matrix(arr, &matrix, &path_mtrx); //маллочим память под матрицу и под path_матрицу
	ft_fill_1st_line(arr, matrix, path_mtrx); //заполняем первую строчку матрицы
	while (i < (*arr)->current - 1)
	{
		ft_find_path_cycle(arr, matrix, path_mtrx, i); //эта функция заполняет матрицу по той логике, что в видео рассказано
		i++;
	}
	ft_print_bf_matrix(matrix, path_mtrx, arr); // просто печать для дебага, можно коммитить.
	path = ft_restore_path(arr, path_mtrx); // воссоздаёт путь из path_матрицы
	ft_free_bf_matrix(arr, matrix, path_mtrx); //чистит память после работы функции
	return (path); //!!! АХТУНГ снаружи надо написать какую-то херабору в которую будут складироваться все найденные пути.
	//!! ахтунг путь отмаллочен, не забыть его пофришить потом
	while (j < i)
		j = j + k + 1;
}

void	ft_expand_graph(t_array **arr, int *path)
{
	//!!! Чтобы ты понимал степень пиздеца происходящего здесь - комменты в этой функции я писал сразу же после написания кода
	//!!! и писал их для себя потому что практически сразу перестаёшь понимать что тут происходит
	//!!! Эта функция реализация вот этого (кроме step4 и step5): http://www.macfreek.nl/memory/Disjoint_Path_Finding - вторая часть статьи где Suurballe

	int		i;
	int 	j;
	t_room	*room;

//	(*arr)->rooms[path[0]]->s_lnk.weights[path[1]] = -1; 	//reverse path - по-моему это уже не надо
	i = 0;
	while (path[i] != -1)
	{
		j = 0;
		// reverse path -->
		while (j < (*arr)->rooms[path[i]]->s_lnk.cur_size)
		{

			if (i != 0 && (*arr)->rooms[path[i]]->s_lnk.links[j] == path[i - 1])
				(*arr)->rooms[path[i]]->s_lnk.weights[j] = -2; // -2 - это стёртые пути
			if ((*arr)->rooms[path[i]]->s_lnk.links[j] == path[i + 1])
				(*arr)->rooms[path[i]]->s_lnk.weights[j] = -1; // -1 - это реверснутые пути
			j++;
		}
		// <-- reverse path
		// --> duplicate room
		if (i != 0 && path[i + 1] != -1)
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
			if (i != 0 && (*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.weights[j] == -1)
				(*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.weights[j] = -2;
			// <-- стирание исходящей ссылки в вершине OUT на прошлую вершину IN в пути
			j++;
		}
		// --> добавление связи между OUT и IN
		if ((*arr)->rooms[path[i]]->s_lnk.room_copy != -1)
			ft_links_push(&((*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk), path[i], 0);
		// <-- добавление связи между OUT и IN
		i++;
	}
}

int ft_path_limit(t_array *arr)
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

void print_path(t_paths *paths, t_array *arr)
{
	// всё что ниже - печать в консоль данных
	int i = 0;
	int j = 0;
	printf("\n");
	t_path *path = paths->path_arr[paths->curr_path - 1];

	while (j < paths->curr_path)
	{
		i = 0;
		while (paths->path_arr[j]->path[i] != -1)
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

t_paths *new_paths()
{
	t_paths *new;

	new = (t_paths *)malloc(sizeof(t_paths));
	new->curr_path = 0;
	new->amount = 0;
	new->path_arr = (t_path **)malloc(sizeof(t_path *) * 100);
	return (new);
}

/*
t_paths *new_paths_sets()
{
	t_paths_sets *new;

	new = (t_paths *)malloc(sizeof(t_paths));
	new->curr_paths_set = 0;
	new->paths_arr[0] = new_paths();
	new->amount = 0;
}
*/

t_path *get_single_path_origin(t_paths *paths, t_array *arr, int path)
{
	t_path *path_origin;
	int j;

	j = 0;
	path_origin = (t_path *)malloc(sizeof(t_path));
	path_origin->size = paths->path_arr[path]->size;
	path_origin->path = (int *)malloc(sizeof(int) * path_origin->size);
	while (j < paths->path_arr[path]->size)
	{
		if (arr->rooms[paths->path_arr[path]->path[j]]->s_lnk.is_copy)
		{
			path_origin->path[j] = arr->rooms[paths->path_arr[path]->path[j]]->s_lnk.room_copy;
		}
		else
			path_origin->path[j] = paths->path_arr[path]->path[j];
		j++;
	}
	return (path_origin);
}

t_path **get_paths_origin(t_paths *paths, t_array *arr)
{
	t_path **paths_origin;
	int i;

	i = 0;
	paths_origin = (t_path **)malloc(sizeof(t_path *) * paths->curr_path);
	while (i < paths->curr_path)
	{
		paths_origin[i] = get_single_path_origin(paths, arr, i);
		i++;
	}
	return (paths_origin);
}

void find_common_edges(t_paths *common_edges, t_path *path_a, t_path *path_b, t_paths *paths)
{
	int i;
	int j;

	i = 1;
	j = 1;
	while (i < path_a->size - 1)
	{
		j = 1;
		while (j < path_b->size - 1)
		{
			if (path_a->path[i] == path_b->path[j + 1] &&
				path_a->path[i + 1] == path_b->path[j])
			{
				common_edges->path_arr[common_edges->curr_path] = \
					(t_path *)malloc(sizeof(t_path));
				common_edges->path_arr[common_edges->curr_path]->path = \
                    (int *)malloc(sizeof(int) * 2);
				common_edges->path_arr[common_edges->curr_path]->path[0] = path_a->path[i];
				common_edges->path_arr[common_edges->curr_path]->path[1] = path_a->path[i + 1];
				common_edges->curr_path++;
			}
			j++;
		}
		i++;
	}
}

void delete_common_edges(t_paths *common_edges, t_paths *paths, t_array *arr)
{
	int i;
	int a;
	int b;

	i = 0;
	while (i < common_edges->curr_path)
	{
		a = common_edges->path_arr[i]->path[0];
		b = common_edges->path_arr[i]->path[1];
		arr->rooms[a]->s_lnk.weights[b] = -2;
		arr->rooms[b]->s_lnk.weights[a] = -2;
		i++;
	}
}

t_paths *handle_common_edges(t_path **orig_paths, t_paths *paths, t_array *arr)
{
	int i;
	int j;
	t_paths *common_edges;

	common_edges = new_paths();
	i = 0;
	while (i < paths->curr_path - 1)
	{
		j = i + 1;
		while (j < paths->curr_path)
		{
			find_common_edges(common_edges, orig_paths[i], orig_paths[j], paths);
			j++;
		}
		paths->path_arr[i]->path;
		i++;
	}
	delete_common_edges(common_edges, paths, arr);
	return (common_edges);
}

void merge_paths(t_paths *paths, t_array *arr)
{
	int i;
	t_path **paths_origin;
	t_path *path;
	t_paths *common_edges;


	paths_origin = get_paths_origin(paths, arr);
	common_edges = handle_common_edges(paths_origin, paths , arr);
	i = 0;
	while (i < paths->curr_path && common_edges->curr_path)
	{
		path = NULL;
		if (path = ft_find_path_bf(&arr, 1, 0, 0))
		{
			free(paths->path_arr[i]);
			paths->path_arr[i] = path;
		}
		i++;
	}
	//free(paths_origin);
}

void copy_t_array(t_array *arr, t_array *arr_copy)
{
	
}

int		main(int argc, char **argv)
{
	t_array *arr;
	t_array *arr_copy;
	int fd;
	t_path *path;
	t_paths *paths;
	t_paths *prev;
	t_paths *curr;
	//t_paths_sets *paths_sets;
	arr = NULL;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	ft_read_data(fd, &arr); //читаем входные данные
//	ft_find_path(&arr);
	path = (t_path *)malloc(sizeof(t_path));
	paths = new_paths();
	paths->path_arr[paths->curr_path] = ft_find_path_bf(&arr, 1, 0, 0);
	//FIND_OPTIMUM();
	paths->amount++;
	paths->curr_path++;
	copy_t_array(arr, arr_copy);
	prev = paths;
	//add_new_path();
	//path->path = ft_find_path_bf(&arr, 1, 0, 0);
	int path_counter = 1;
	int path_limit = ft_path_limit(arr);
	while (path_counter < path_limit)
	{
		ft_expand_graph(&arr, paths->path_arr[paths->curr_path - 1]->path);
		paths->path_arr[paths->curr_path] = ft_find_path_bf(&arr, 1, 0, 0);
		if (!paths->path_arr[paths->curr_path])
			break;
		paths->amount++;
		paths->curr_path++;
		merge_paths(paths, arr);
		//path->path = ft_find_path_bf(&arr, 1, 0, 0);
		path_counter++;
	}
	print_path(paths, arr);
//	printf("%d", arr->rooms[3]->s_lnk.weights[1]);
	return (0);
}



// --> замена исходящей ссылки в вершине OUT на прошлую вершину IN в пути на собственный (IN)
//			if (i != 0 && (*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.weights[j] == -1)
//			{
//				(*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.weights[j] = 0;
//				(*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy]->s_lnk.links[j] = path[i];
//			}
// <-- замена исходящей ссылки в вершине OUT на прошлую вершину IN в пути на собственный (IN)