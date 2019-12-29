/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:18:00 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/10 14:39:16 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *str_search, size_t count)
{
	size_t	i;
	size_t	j;

	if (str_search[0] == '\0')
		return ((char *)str);
	if (str[0] == '\0')
		return (NULL);
	i = 0;
	while (i < count && str[i] != '\0')
	{
		j = 0;
		while (i + j < count && str[i + j] == str_search[j]
				&& str_search[j] != '\0')
			j++;
		if (str_search[j] == '\0')
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
