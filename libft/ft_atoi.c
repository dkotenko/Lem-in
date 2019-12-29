/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:15:20 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/11 13:49:54 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long long int	i;
	long long int	result;
	long long int	neg;

	i = 0;
	result = 0;
	neg = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
			str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		neg = (str[i++] == '+') ? 1 : -1;
	while (str[i] <= '9' && str[i] >= '0')
	{
		result = result * 10 + str[i] - '0';
		if (result >= 922337203685477580 && neg > 0 && ((str[i] - '0') > 7))
			return (-1);
		if (result >= 922337203685477580 && neg < 0 && ((str[i] - '0') > 8))
			return (0);
		i++;
	}
	return ((int)(result * neg));
}
