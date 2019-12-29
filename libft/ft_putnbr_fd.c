/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:52:36 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/10 15:17:40 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_reverse_str(char *s)
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
}

static void	ft_itoa_static(char *str, int n)
{
	int		i;
	long	buf;

	buf = n;
	if (n < 0)
		buf = -buf;
	i = 0;
	while (buf > 0)
	{
		str[i] = buf % 10 + '0';
		buf = buf / 10;
		i++;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
}

void		ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	int		i;

	if (n == 0)
		ft_putchar_fd('0', fd);
	ft_itoa_static(str, n);
	ft_reverse_str(str);
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
}
