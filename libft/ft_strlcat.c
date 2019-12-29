/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:04:58 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/05 15:30:37 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *str_destination, const char *str_source, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str_destination[i] && i < count)
		i++;
	while ((str_source[j]) && ((i + j + 1) < count))
	{
		str_destination[i + j] = str_source[j];
		j++;
	}
	if (i != count)
		str_destination[i + j] = '\0';
	return (i + ft_strlen((char *)str_source));
}
