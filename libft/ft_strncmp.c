/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:52:58 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/09 13:41:41 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t i)
{
	unsigned long	a;
	unsigned char	*str1;
	unsigned char	*str2;

	a = 0;
	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	if (i == 0)
		return (0);
	while (*str1 && *str2 && *str1 == *str2 && a < i - 1)
	{
		str1++;
		str2++;
		a++;
	}
	return (*str1 - *str2);
}
