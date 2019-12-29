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

int		*ft_restore_path(t_array **arr, int **path_mtrx)
{
	int *path;
	int i;
	int j;
	int k;

	path = (int*)malloc(sizeof(int) * (*arr)->current - 1);
	ft_fill_mem(path, (*arr)->current - 1, -1);
	i = (*arr)->current - 2;
	j = (*arr)->finish;
	k = 1;
	path[0] = (*arr)->finish;
	while (path_mtrx[i][j] != (*arr)->start)
	{
		//printf("%d\n", path[k - 1]);
		path[k] = path_mtrx[i][j];
		k++;
		j = path_mtrx[i][j];
		i--;
	}
	path[k] = (*arr)->start;
//	while (*path != -1)
//	{
//		printf("%d ", *path);
//		path++;
//	}
	return (path);
}

int		*ft_find_path_bf(t_array **arr, int i, int j, int k)
{
	int	**matrix; //беллман форд работает через матрицу.
	// Посмотри видос с названием "M46 Bellman Ford Algm single source" на ютубе.
	// Длина видоса 15.44. Смотреть с 6.00 по 11.30 минуты

	int **path_mtrx; //сюда я записываю индексы комнат, чтобы потом по ним восстановить путь (про это в видосе не говорится)
	int	*path; //это итоговый путь который возвращает функция (массив интов)

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

int		main(int argc, char **argv)
{
	t_array	*arr;
	int		fd;
	int		*path;

	arr = NULL;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	ft_read_data(fd, &arr); //читаем входные данные
//	ft_find_path(&arr);
	path = ft_find_path_bf(&arr, 1, 0, 0);
	ft_expand_graph(&arr, path);
	path = ft_find_path_bf(&arr, 1, 0, 0);
	// всё что ниже - печать в консоль данных
	int i = 0;
	int j = 0;
	printf("\n");
	while (*path != -1)
	{
		printf("%s-", arr->rooms[*path]->name);
		path++;
	}
	printf("\n");
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