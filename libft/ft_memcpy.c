/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:38:46 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/10 13:15:34 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dp;
	char	*sp;

	if (n == 0 || dest == src)
		return (dest);
	i = 0;
	dp = (char *)dest;
	sp = (char *)src;
	while (i < n)
	{
		*dp = *sp;
		i++;
		dp++;
		sp++;
	}
	return (dest);
}
