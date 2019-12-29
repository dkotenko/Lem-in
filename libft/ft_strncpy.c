/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:14:34 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/05 15:26:11 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *str_destination, const char *str_source, size_t count)
{
	size_t	i;

	i = 0;
	while (str_source[i] != '\0' && i < count)
	{
		str_destination[i] = str_source[i];
		i++;
	}
	while (i < count)
	{
		str_destination[i] = '\0';
		i++;
	}
	return (str_destination);
}
