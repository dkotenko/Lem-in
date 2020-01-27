/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:47:51 by ksticks           #+#    #+#             */
/*   Updated: 2019/10/17 15:47:57 by ksticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	count_digits(ulong n, uint base)
{
	uint i;

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

char			*ft_ultoa_buf(char *s, ulong n, uint base)
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

char			*ft_ultoa(ulong n)
{
	size_t	d;
	char	*s;

	d = count_digits(n, 10);
	if (!(s = malloc(sizeof(char) * (d + 1))))
		return (0);
	ft_ultoa_buf(s, n, 10);
	return (s);
}

char			*ft_ultoa_base(ulong n, uint base)
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
