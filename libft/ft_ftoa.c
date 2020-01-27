/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:23:42 by ksticks           #+#    #+#             */
/*   Updated: 2019/10/17 15:23:45 by ksticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "libft_math.h"

static ullong		mod(long double a, int b)
{
	if (a > (long double)ULLONG_MAX)
		return (0);
	return (((ullong)a) % b);
}

static long double	round_to_even(long double x, int decimals, int base)
{
	long double pow;

	pow = (long double)ft_ullpow(base, decimals);
	if (mod((x > 0 ? x : -x) * pow, 2))
		return (x + .5 / pow);
	if (.5 / pow + (long double)((ullong)(x * pow)) / pow - x)
		return (x + .5 / pow);
	return (x);
}

void				ftoa_inner(long double x, char *b, int decimals, int base)
{
	long double	y;
	char		*ptr;

	ptr = b;
	y = x;
	if (y < 1.)
		*ptr++ = '0';
	while (y >= 1.)
	{
		*ptr++ = '0' + (int)mod(y, base);
		y /= base;
	}
	*ptr = 0;
	ft_strrev(b);
	if (decimals)
		*ptr++ = '.';
	while (decimals--)
	{
		x *= base;
		*ptr++ = '0' + (int)(mod(x, base));
	}
	*ptr = 0;
}

char				*ft_ftoa_buf(char *s, long double n, int decimals)
{
	char		*ptr;
	int			base;

	base = 10;
	ptr = s;
	if (n < 0)
	{
		*ptr++ = '-';
		n *= -1;
	}
	ftoa_inner(round_to_even(n, decimals, base), ptr, decimals, base);
	return (s);
}

char				*ft_ftoa(long double n, int decimals)
{
	size_t	d;
	char	*s;
	int		base;

	base = 10;
	d = ft_count_int_digits((long int)n, base) + decimals + 1;
	if (!(s = malloc(sizeof(char) * (d + 1))))
		return (0);
	return (ft_ftoa_buf(s, n, decimals));
}
