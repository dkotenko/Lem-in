/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 13:39:55 by clala             #+#    #+#             */
/*   Updated: 2020/01/19 17:40:13 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static int		is_valid_status_ants(char *s, t_input *input, t_array *arr)
{
	int number;

	number = ft_atoi(s);	
	if (!ft_isdigit(s[0]) || ft_ilen(number) != ft_strlen(s))
		handle_error("Invalid number of ants", input, arr);
	else if (!number)
		handle_error("There are no ants", input, arr);
	input->status = STATUS_BEFORE_START;
	return (1);
}

static int		is_valid_status_STATUS_BEFORE_START_end(char *s, t_input *input, t_array *arr)
{
	if (input->status == STATUS_BEFORE_START && ft_strcmp(s, "##start") == 0)
	{
		input->status = STATUS_IS_START;
		return (1);
	}
	else if (input->status == STATUS_BEFORE_END && ft_strcmp(s, "##end") == 0)
	{
		input->status = STATUS_IS_END;
		return (1);
	}
	if (!is_valid_room(s, input, arr))
		handle_error("Invalid room", input, arr);
	return (1);
}

int		is_valid_line(char *s, t_input *in, t_array *arr)
{
	!s[0] || !s ? handle_error("Empty line", in, arr) : 1;
	if (in->status == STATUS_ANTS)
		is_valid_status_ants(s, in, arr);
	else if (in->status == STATUS_BEFORE_START || in->status == STATUS_BEFORE_END)
		is_valid_status_STATUS_BEFORE_START_end(s, in, arr);
	else if (in->status == STATUS_IS_START || in->status == STATUS_IS_END)
	{
		if (!is_valid_room(s, in, arr))
			handle_error("Invalid room", in, arr);
		in->status = (in->status == STATUS_IS_START ?
			STATUS_BEFORE_END : STATUS_AFTER_END);
	}			
	else if (in->status == STATUS_AFTER_END)
	{
		if (!ft_strchr(s, ' ') && is_valid_link(s, in, arr))
			in->status = STATUS_LINKS;
		else if (!is_valid_room(s, in, arr))
			handle_error("Invalid room", in, arr);
	}	
	else if (in->status == STATUS_LINKS && !is_valid_link(s, in, arr))

	return (1);
}
