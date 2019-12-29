/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:35:52 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/05 13:36:57 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buffer, int c, size_t count)
{
	char	*buffer2;

	buffer2 = (char*)buffer;
	while (count)
	{
		if (*buffer2 == (char)c)
		{
			return ((char*)buffer2);
		}
		buffer2++;
		count--;
	}
	return (NULL);
}
