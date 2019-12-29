/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:02:29 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/10 14:21:41 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		sizes1;
	int		sizes2;

	if (!s1 || !s2)
		return (NULL);
	sizes1 = ft_strlen((char *)s1);
	sizes2 = ft_strlen((char *)s2);
	if (!(str = (char *)malloc(sizeof(char) * (sizes1 + sizes2) + 1)))
		return (NULL);
	i = 0;
	while (i < sizes1)
	{
		(str[i] = s1[i]);
		i++;
	}
	i = 0;
	while (i < sizes2)
	{
		str[sizes1 + i] = s2[i];
		i++;
	}
	str[sizes1 + sizes2] = '\0';
	return (str);
}
