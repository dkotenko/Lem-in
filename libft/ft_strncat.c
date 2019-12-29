/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:12:00 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/05 14:14:08 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *str_destination,
		const char *str_source, size_t count)
{
	char	*result;
	size_t	i;

	result = str_destination;
	i = 0;
	while (*str_destination != '\0')
	{
		str_destination++;
	}
	while (*str_source != '\0' && i < count)
	{
		*str_destination = *str_source;
		str_destination++;
		str_source++;
		i++;
	}
	*str_destination = '\0';
	return (result);
}
