/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_array.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:47:48 by clala             #+#    #+#             */
/*   Updated: 2020/02/05 21:01:54 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem-in.h"

void		t_array_free(t_array *arr)
{
	int		i;

	i = arr->max;
	while (--i > -1)
	{
		if (arr->rooms[i])
			t_room_free(arr->rooms[i]);
	}
	free(arr->rooms);
	free(arr);
}

t_array		*t_array_copy(t_array *arr)
{
	int		i;
	t_array	*arr_copy;

	arr_copy = (t_array *)malloc(sizeof(t_array));
	arr_copy->max = arr->max;
	arr_copy->current = arr->current;
	arr_copy->start = arr->start;
	arr_copy->finish = arr->finish;
	arr_copy->ants = arr->ants;
	arr_copy->rooms = (t_room **)malloc(sizeof(t_room *) * arr->max);
	i = 0;
	while (i < arr->max)
	{
		arr_copy->rooms[i] = NULL;
		i++;
	}
	return (arr_copy);
}
