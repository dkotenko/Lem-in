#include "../includes/lem-in.h"
#include "../libft/libft.h"

t_ant	*ft_ants_creator()
{
	static int	num = 1;
	char		let[2];
	char 		*numb;
	t_ant		*clone;

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

	order = 1;
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

void	ft_ants_prepare_to_parade(t_array **arr, t_paths *paths)
{
	t_ant	*ants;
	t_ant	*first_ant;
	int 	i;
	int		j;
	int 	min_path;
	int 	min_path_num;

	curr_size_to_size(paths);
	ants = ft_ants_creator();
	first_ant = ants;
	i = 0;

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
		ants->next = ft_ants_creator(); // !!!! создаётся на 1 муравья больше чем надо и это ок
		ants = ants->next;
		i++;
	}
	ants = first_ant;
	while (ants->next != NULL)
	{
			//printf("name: %s, p:%d, o:%d\n", ants->name, ants->path, ants->order);
		ants = ants->next;
	}
	ants = first_ant;
	ft_list_sort(ants);
	ft_ants_parade(arr, ants, paths);
}