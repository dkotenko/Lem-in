/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:06:06 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/10 14:47:45 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_reverse(char *s)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
	return (s);
}

static	int		ft_countlen(int n)
{
	int i;

	i = 0;
	if (n < 0)
		i++;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

static	char	*ft_returnzero(void)
{
	char *result;

	result = (char *)malloc(2);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

char			*ft_itoa(int n)
{
	int		i;
	long	buf;
	char	*result;

	if (n == 0)
		return (ft_returnzero());
	buf = n;
	if (n < 0)
		buf = -buf;
	i = 0;
	result = (char *)malloc(sizeof(char) * ft_countlen(buf) + 1);
	if (result == NULL)
		return (NULL);
	while (buf > 0)
	{
		result[i] = buf % 10 + '0';
		buf = buf / 10;
		i++;
	}
	if (n < 0)
		result[i++] = '-';
	result[i] = '\0';
	return (ft_reverse(result));
}
