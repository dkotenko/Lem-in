#include "../includes/lem-in.h"
#include "../libft/libft.h"

void	ft_expand_graph(t_array **arr, int *path, int size)
{
	int		i;
	int 	j;
	t_room	*room;

	printf("ENTER\n");
	print_t_array_rooms_with_links(*arr);
	i = 0;
	while (i < size)
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
			if (i < size - 1 && (*arr)->rooms[path[i]]->s_lnk.links[j] == path[i + 1])
					(*arr)->rooms[path[i]]->s_lnk.weights[j] = -1;
			j++;
		}
//		printf("\n");
		// <-- reverse path
		i++;
	}
	i = 1;
	while (i < size - 1)
	{
		// --> duplicate room
//		printf("name: %s\n", (*arr)->rooms[path[i]]->name);
		if ((*arr)->rooms[path[i]]->s_lnk.room_copy == -1)
		{
			room = (t_room*)malloc(sizeof(t_room));
			ft_cpy_room_data(room, (*arr)->rooms[path[i]], (*arr)->current, path[i]);
			ft_arr_push(arr, room);
		}
		else
			ft_cpy_room_data((*arr)->rooms[(*arr)->rooms[path[i]]->s_lnk.room_copy], (*arr)->rooms[path[i]], (*arr)->rooms[path[i]]->s_lnk.room_copy, path[i]);
		// <-- duplicate room
		i++;
	}

	i = 0;
	while (i < size - 1)
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
	printf("exit\n");
	print_t_array_rooms_with_links(*arr);
}
