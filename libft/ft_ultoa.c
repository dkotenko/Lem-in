/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:47:51 by ksticks           #+#    #+#             */
/*   Updated: 2020/02/13 20:50:55 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	count_digits(ULONG n, UINT base)
{
	UINT i;

	if (n == 0)
		return (1);
	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

char			*ft_ultoa_buf(char *s, ULONG n, UINT base)
{
	size_t	d;
	char	c;
	int		rem;

	d = count_digits(n, base);
	s[d] = 0;
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		rem = (int)(n % base);
		if (rem > 9)
			c = 'a' + rem - 10;
		else
			c = '0' + rem;
		s[d-- - 1] = c;
		n /= base;
	}
	return (s);
}

char			*ft_ultoa(ULONG n)
{
	size_t	d;
	char	*s;

	d = count_digits(n, 10);
	if (!(s = malloc(sizeof(char) * (d + 1))))
		return (0);
	ft_ultoa_buf(s, n, 10);
	return (s);
}

char			*ft_ultoa_base(ULONG n, UINT base)
{
	size_t	d;
	char	*s;

	if (base < 2 || base > 32)
		return (0);
	d = count_digits(n, base);
	if (!(s = malloc(sizeof(char) * (d + 1))))
		return (0);
	ft_ultoa_buf(s, n, base);
	return (s);
}
