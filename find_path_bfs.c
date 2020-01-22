#include "lem-in.h"
#include "libft/libft.h"

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
	ft_fill_mem(path->path, (*arr)->current, -1);
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
//	while (i < path->size)
//	{
//		printf("%s-", (*arr)->rooms[path->path[i]]->name);
////		printf("%d-", path->path[i]);
//		i++;
//	}
//	printf("\n");
	path->order = 1;

	return (path);
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
//			if (rooms[rooms[*queue]->s_lnk.links[i]]->s_lnk.room_copy != -1) //если вершина разделённая то ищем IN или OUT она
//			{
//				if (rooms[*queue]->s_lnk.weights[i] == 1 && rooms[rooms[*queue]->s_lnk.links[i]]->flag != 2)
//					rooms[rooms[*queue]->s_lnk.links[i]]->flag = 2; //если пришли по положительному пути - это IN вершина
//				if (rooms[*queue]->s_lnk.weights[i] == -1)
//					rooms[rooms[*queue]->s_lnk.links[i]]->flag = 1; //если пришли по отрицательному пути - это OUT вершина
//			}
//			if ((rooms[*queue]->flag == -1) || (rooms[*queue]->flag == 2 && rooms[*queue]->s_lnk.weights[i] == -1) || (rooms[*queue]->flag == 1 && rooms[*queue]->s_lnk.weights[i] == 1))
//				если текущая комната, что мы смотрим - не разделённая то просто пушим найденный линк в очередь || Или комната IN и вес отрицательный || или комната OUT и вес положительный
//			{
			**cur_queue = rooms[*queue]->s_lnk.links[i];
			rooms[rooms[*queue]->s_lnk.links[i]]->s_lnk.order = rooms[*queue]->s_lnk.order + 1;
			if (rooms[*queue]->s_lnk.room_copy != -1)
				rooms[rooms[*queue]->s_lnk.room_copy]->s_lnk.order = rooms[*queue]->s_lnk.order;
			(*cur_queue)++;
			if (rooms[*queue]->s_lnk.links[i] == (*arr)->finish)
				return (1);
//			}
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

//	print_t_array_rooms_with_links(*arr);
//	ft_restore_path_bfs(arr);
	return ft_restore_path_bfs_smart(arr);
}