/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ilen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:47:48 by clala             #+#    #+#             */
/*   Updated: 2019/11/26 20:27:04 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_ant	*ft_ants_creator(void)
{
	static int	num = 1;
	char		let[2];
	char		*numb;
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

size_t		ft_ilen(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}
