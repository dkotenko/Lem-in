/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:41:40 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/10 16:26:25 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	unsigned char	*src2;
	unsigned char	*dest2;

	if (count == 0 || dest == src)
		return ((char *)dest);
	src2 = (unsigned char*)src;
	dest2 = (unsigned char*)dest;
	if (dest2 < src2)
		while (count--)
		{
			*dest2++ = *src2++;
		}
	else
	{
		dest2 += count;
		src2 += count;
		while (count--)
		{
			dest2--;
			src2--;
			*dest2 = *src2;
		}
	}
	return (dest);
}
