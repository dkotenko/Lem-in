/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:54:11 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/05 13:55:19 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *str_destination, const char *str_source)
{
	int	i;

	i = 0;
	while (str_source[i] != '\0')
	{
		str_destination[i] = str_source[i];
		i++;
	}
	str_destination[i] = '\0';
	return (str_destination);
}
