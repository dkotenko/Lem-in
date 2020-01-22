#include "lem-in.h"
#include "libft/libft.h"

void	ft_expand_graph(t_array **arr, int *path)
{
	int		i;
	int 	j;
	t_room	*room;
//printf("\n");
//	print_t_path(path, *arr);
//	printf("\n");

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
