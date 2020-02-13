/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:44:05 by ksticks           #+#    #+#             */
/*   Updated: 2020/02/13 21:03:00 by clala            ###   ########.fr       */
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

ULLONG	ft_ullpow(ULLONG a, ULLONG b)
{
	ULLONG r;

	r = 1;
	while (b--)
		r *= a;
	return (r);
}
