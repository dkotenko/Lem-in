/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemins.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 13:39:55 by clala             #+#    #+#             */
/*   Updated: 2019/12/24 21:03:13 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int	handle_error(char *s, t_input *input, t_array *arr)
{
	ft_fprintf(2, "ERROR in line %d: %s\n", input->lines_counter, s);
	exit(1);
	return (1);
}
