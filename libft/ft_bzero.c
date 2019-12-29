/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:21:45 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/05 15:03:16 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *destination, size_t n)
{
	size_t	i;
	char	*test;

	i = 0;
	test = destination;
	while (i < n)
	{
		test[i] = 0x00;
		i++;
	}
}
