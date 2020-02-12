/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_paths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:00:39 by edrowzee          #+#    #+#             */
/*   Updated: 2020/02/12 14:00:40 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	t_paths_free(t_paths *paths)
{
	while (--(paths->curr_path) > -1)
		t_path_free(paths->path_arr[paths->curr_path]);
	free(paths->path_arr);
	free(paths);
}

t_paths	*copy_t_paths(t_paths *paths)
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

void	ft_paths_sort(t_paths *paths)
{
	int	i;

	i = -1;
	while (++i < paths->curr_path)
	{
		ft_path_sort(paths->path_arr[i]);
	}
}

t_paths	*create_t_paths(void)
{
	t_paths *new;

	new = (t_paths *)malloc(sizeof(t_paths));
	new->curr_path = 0;
	new->path_arr = (t_path **)malloc(sizeof(t_path *) * 1000);
	return (new);
}
