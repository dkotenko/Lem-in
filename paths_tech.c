#include "lem-in.h"
#include "libft/libft.h"

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