/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:44:05 by ksticks           #+#    #+#             */
/*   Updated: 2019/10/17 15:44:07 by ksticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_compat.h"
#include "libft.h"

int		ft_pow(int a, int b)
{
	int r;

	r = 1;
	if (b < 0)
		return (0);
	while (b--)
		r *= a;
	return (r);
}

ullong	ft_ullpow(ullong a, ullong b)
{
	ullong r;

	r = 1;
	while (b--)
		r *= a;
	return (r);
}

REAL	ft_fpow(REAL a, int b)
{
	REAL r;

	r = 1.;
	while (b > 0)
	{
		r *= a;
		b--;
	}
	while (b < 0)
	{
		r /= a;
		b++;
	}
	return (r);
}
