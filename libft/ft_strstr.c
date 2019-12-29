/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:24:38 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/05 14:26:06 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *str_search)
{
	int	i;
	int	j;

	i = 0;
	if (*str_search == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == str_search[j] && str_search[j] != '\0')
			j++;
		if (str_search[j] == '\0')
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
