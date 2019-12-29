/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:33:22 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/05 13:35:09 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t count)
{
	char	*dest2;
	char	*src2;

	dest2 = (char*)dest;
	src2 = (char*)src;
	while (count)
	{
		*dest2 = *src2;
		if (*dest2 == (char)c)
		{
			dest2++;
			return ((char*)dest2);
		}
		dest2++;
		src2++;
		count--;
	}
	return (NULL);
}
