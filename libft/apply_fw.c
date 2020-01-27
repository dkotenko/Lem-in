/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_fw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:21:57 by edrowzee          #+#    #+#             */
/*   Updated: 2019/10/16 13:47:52 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"
#include "libft_compat.h"

static void	apply_fw_width(char *b, char fill_c, t_printf_spec s, size_t len)
{
	if (s.field_width > len)
	{
		if (s.flags & PRINTF_MINUS)
			ft_memset(b + len, ' ', s.field_width - len);
		else
		{
			ft_memmove(b + s.field_width - len, b, len + 1);
			ft_memset(b, fill_c, s.field_width - len);
		}
		b[s.field_width] = 0;
	}
}

char		*apply_fw(char *b, t_printf_spec s)
{
	char	fill_c;
	size_t	len;
	char	*b_initial;

	fill_c = ' ';
	b_initial = b;
	if (s.flags & PRINTF_ZERO && (ft_strchr("diouxXpf", s.type) || MACOS)
		&& (s.type == 'f' || s.precision < 0))
	{
		fill_c = '0';
		b += s.prefix_w;
		if (s.field_width < s.prefix_w)
			s.field_width = 0;
		else
			s.field_width -= s.prefix_w;
	}
	len = ft_strlen(b);
	apply_fw_width(b, fill_c, s, len);
	return (b_initial);
}
