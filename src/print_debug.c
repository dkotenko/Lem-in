#include "../includes/lemin.h"
#include "../libft/libft.h"

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
	while(++i < arr->current)
	{
		if (!arr->rooms[i])
			continue ;
		ft_putstr("ROOM:");
		ft_putstr(arr->rooms[i]->name);
		ft_putstr(": ");
		printf("(o: %d src: %d) | ", arr->rooms[i]->order, arr->rooms[i]->src);
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
