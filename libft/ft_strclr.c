/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:51:12 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/10 13:55:17 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *s)
{
	int	strlength;
	int	i;

	if (s)
	{
		strlength = ft_strlen(s);
		i = 0;
		while (i < strlength)
		{
			s[i] = 0x00;
			i++;
		}
	}
}
