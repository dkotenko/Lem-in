/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:49:59 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/12 16:40:45 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = (char *)str;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == (char)c)
			return (buffer + i);
		i++;
	}
	if (buffer[i] == '\0' && c == '\0')
		return (buffer + i);
	return (NULL);
}
