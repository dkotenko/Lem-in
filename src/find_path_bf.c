/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_bf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:25:14 by edrowzee          #+#    #+#             */
/*   Updated: 2020/02/12 13:25:15 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include "../libft/libft.h"

static t_path	*find_path_bf_new_ret(t_array **arr)
{
	t_path	*result;
	int		i;
	int		len;

	result = (t_path *)malloc(sizeof(t_path));
	i = (*arr)->finish;
	len = 1;
	while (i != (*arr)->start)
	{
		i = (*arr)->rooms[i]->src;
		len++;
	}
	result->size = len;
	result->path = (int*)malloc(sizeof(int) * result->size);
	i = 1;
	result->path[0] = (*arr)->finish;
	result->curr_size = 0;
	while (i < result->size)
	{
		result->path[i] = (*arr)->rooms[result->path[i - 1]]->src;
		i++;
	}
	return (result);
}

static void		find_path_bf_new_cycle2(t_array **arr,
		int *is_weight_modify, int i, int j)
{
	if ((*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->order >
		(*arr)->rooms[i]->order + (*arr)->rooms[i]->s_lnk.weights[j])
	{
		if ((*arr)->rooms[i]->s_lnk.weights[j] == 0)
		{
			(*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->order =
					(*arr)->rooms[i]->order;
			(*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->src =
					(*arr)->rooms[i]->src;
		}
		else
		{
			(*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->order =
				(*arr)->rooms[i]->order + (*arr)->rooms[i]->s_lnk.weights[j];
			(*arr)->rooms[(*arr)->rooms[i]->s_lnk.links[j]]->src = i;
		}
		*is_weight_modify = 1;
	}
}

static void		find_path_bf_new_cycle(t_array **arr, int *is_weight_modify)
{
	int i;
	int j;

	i = -1;
	while (++i < (*arr)->current)
	{
		j = -1;
		if ((*arr)->rooms[i]->order != INT_MAX)
		{
			while (++j < (*arr)->rooms[i]->s_lnk.cur_size)
			{
				if ((*arr)->rooms[i]->s_lnk.weights[j] != -2)
					find_path_bf_new_cycle2(arr, is_weight_modify, i, j);
			}
		}
	}
}

t_path			*find_path_bf_new(t_array **arr)
{
	t_path	*result;
	int		i;
	int		is_weight_modify;

	i = 0;
	is_weight_modify = 1;
	(*arr)->rooms[(*arr)->start]->order = 0;
	while (i < (*arr)->current && is_weight_modify)
	{
		is_weight_modify = 0;
		find_path_bf_new_cycle(arr, &is_weight_modify);
		i++;
	}
	if ((*arr)->rooms[(*arr)->finish]->order == INT_MAX)
		return (NULL);
	result = find_path_bf_new_ret(arr);
	result->order = 1;
	reset_order_src(arr);
	return (result);
}
