/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:48:06 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/05 13:49:42 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *str_destination, const char *str_source)
{
	char	*result;

	result = str_destination;
	while (*str_destination != '\0')
	{
		str_destination++;
	}
	while (*str_source != '\0')
	{
		*str_destination = *str_source;
		str_destination++;
		str_source++;
	}
	*str_destination = '\0';
	return (result);
}
