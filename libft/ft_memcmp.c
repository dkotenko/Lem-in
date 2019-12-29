/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:37:41 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/09 12:43:06 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buffer1, const void *buffer2, size_t count)
{
	unsigned char	*temp1;
	unsigned char	*temp2;

	temp1 = (unsigned char*)buffer1;
	temp2 = (unsigned char*)buffer2;
	while (count)
	{
		if (*temp1 != *temp2)
			return (*temp1 - *temp2);
		else
		{
			temp1++;
			temp2++;
		}
		count--;
	}
	return (0);
}
