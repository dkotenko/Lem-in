/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 13:39:55 by clala             #+#    #+#             */
/*   Updated: 2020/02/05 20:44:27 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	is_room_coords_unique(char *coords, t_input *input)
{
	int		hash_coords;

	hash_coords = input->ht->coords->hash(coords, input->ht->coords->size);
	if (!t_htable_find(hash_coords, coords, input->ht->coords))
		return (1);
	return (0);

}

static int	is_room_name_unique(char *name, t_input *input)
{
	int		hash_name;	

	hash_name = input->ht->names->hash(name, input->ht->names->size);	
	if (!t_htable_find(hash_name, name, input->ht->names))
		return (1);
	return (0);
}
	


static int	is_integer(char *s, int n)
{
	size_t	len;

	len = ft_strlen(s);
	if ((s[0] != '-' && !ft_isdigit(s[0])) || len != ft_ilen(n))
		return (0);
	return (1);	
}

void		check_room_name(char **arr_split, t_input *input, t_array *arr)
{
	int		i;
	char	*s;

	s = arr_split[0];
	i = -1;
	while(s[++i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			ft_split_free(arr_split);		
			handle_error("Invalid character in room name", input, arr);
		}
	}
}

int			is_valid_room(char *s, t_input *input, t_array *arr)
{
	char	**arr_split;
	int		x;
	int		y;

	if (s[0] == 'L')
		handle_error("Room`s name starts with 'L'", input, arr);
	arr_split = ft_strsplit(s, ' ');
	if ((!arr_split[0] || !arr_split[1] ||
		!arr_split[2] || arr_split[3]) && ft_split_free(arr_split))
		handle_error("Invalid room", input, arr);	
	check_room_name(arr_split, input, arr);
	x = ft_atoi(arr_split[1]);
	y = ft_atoi(arr_split[2]);
	if  ((!is_integer(arr_split[1], x) || !is_integer(arr_split[2], y)) &&
	ft_split_free(arr_split))
		handle_error("Room`s coords are not integers", input, arr);	
	if (!is_room_name_unique(arr_split[0], input) && ft_split_free(arr_split))
		handle_error("Room with the same name already exists", input, arr);
	if (!is_room_coords_unique(ft_strchr(s, ' ') + 1, input) &&
	ft_split_free(arr_split))
		handle_error("Room with the same coords exists", input, arr);
	ft_split_free(arr_split);
	return (1);	
}

