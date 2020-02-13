/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 13:39:55 by clala             #+#    #+#             */
/*   Updated: 2020/02/13 20:14:51 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int	handle_error(char *s, t_input *input, t_array *arr)
{
	ft_fprintf(2, "ERROR in line %d: %s\n", input->lines_counter, s);
	t_input_free(input);
	t_array_free(arr);
	exit(0);
	return (1);
}
