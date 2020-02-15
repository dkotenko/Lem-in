/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:40:23 by edrowzee          #+#    #+#             */
/*   Updated: 2020/02/15 14:37:40 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/libft.h"

void	ft_parade_cyc(t_array **arr, t_paths *paths,
		t_ant *ants, int *is_all_finished)
{
	static int	order = 1;

	while (ants->next != NULL)
	{
		if (ants->order == order && ants->position
		< paths->path_arr[ants->path]->size - 1)
		{
			ants->position += 1;
			ants->order += 1;
			ft_printf("%s-%s ", ants->name, (*arr)->rooms[paths->
					path_arr[ants->path]->path[ants->position]]->name);
			*is_all_finished = 0;
		}
		ants = ants->next;
	}
	order++;
}

void	ft_ants_parade(t_array **arr, t_ant *ants, t_paths *paths)
{
	t_ant	*first_ant;
	int		is_all_finished;

	first_ant = ants;
	is_all_finished = 0;
	ft_paths_sort(paths);
	ft_printf("\n");
	while (!is_all_finished)
	{
		is_all_finished = 1;
		ants = first_ant;
		ft_parade_cyc(arr, paths, ants, &is_all_finished);
		if (!is_all_finished)
			ft_printf("\n");
	}
	while (ants->next)
	{
		first_ant = ants->next;
		free(ants->name);
		free(ants);
		ants = first_ant;
	}
	free(ants->name);
	free(ants);
}

void	ft_list_sort(t_ant *ants)
{
	t_ant	*start;
	int		path;
	int		order;

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

void	ft_ants_cyc(t_paths *paths, int *min_path, int *min_path_num)
{
	int j;

	*min_path = 1000000;
	*min_path_num = -1;
	j = -1;
	while (++j < paths->curr_path)
	{
		if (paths->path_arr[j]->curr_size < *min_path)
		{
			*min_path = paths->path_arr[j]->curr_size;
			*min_path_num = j;
		}
	}
	if (*min_path_num == -1)
	{
		ft_printf("Error: some problems with shortest path\n");
		exit(1);
	}
}

void	ft_ants_prepare_to_parade(t_array **arr, t_paths *paths, int i)
{
	t_ant	*ants;
	t_ant	*first_ant;
	int		min_path;
	int		min_path_num;

	curr_size_to_size(paths);
	ants = ft_ants_creator();
	first_ant = ants;
	while (++i < (*arr)->ants)
	{
		ft_ants_cyc(paths, &min_path, &min_path_num);
		paths->path_arr[min_path_num]->curr_size += 1;
		ants->path = min_path_num;
		ants->order = paths->path_arr[min_path_num]->order;
		paths->path_arr[min_path_num]->order += 1;
		ants->next = ft_ants_creator();
		ants = ants->next;
	}
	ants = first_ant;
	ft_list_sort(ants);
	ft_ants_parade(arr, ants, paths);
	t_array_free(*arr);
}
