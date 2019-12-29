/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:20:44 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/07 16:05:59 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*buffer;
	int		i;

	i = ft_strlen((char *)str);
	buffer = (char *)str;
	while (i >= 0)
	{
		if (buffer[i] == (char)c)
			return (buffer + i);
		i--;
	}
	return (NULL);
}
