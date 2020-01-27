/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:21:57 by edrowzee          #+#    #+#             */
/*   Updated: 2019/10/16 13:49:37 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

void			prepend_str(char *buff, const char *s)
{
	size_t len;

	len = ft_strlen(s);
	ft_memmove(buff + len, buff, ft_strlen(buff) + 1);
	ft_memcpy(buff, s, len);
}

char			*convert_uint(char *b, ullong v, t_printf_spec *s)
{
	if (s->type == 'u')
		ft_ultoa_buf(b, v, 10);
	else if (s->type == 'o')
		ft_ultoa_buf(b, v, 8);
	else if (ft_tolower(s->type) == 'x')
		ft_ultoa_buf(b, v, 16);
	if (!s->precision && !v && (!(s->flags & PRINTF_HASH)
								| (ft_tolower(s->type) == 'x')))
		b[0] = 0;
	if ((s->flags & PRINTF_HASH) && v && s->type == 'o')
	{
		prepend_str(b, "0");
		s->prefix_w = 1;
	}
	while (s->precision > (int)ft_strlen(b))
		prepend_str(b, "0");
	if ((s->flags & PRINTF_HASH) && ft_tolower(s->type) == 'x' && v)
	{
		prepend_str(b, "0x");
		s->prefix_w = 2;
	}
	if (s->type == 'X')
		ft_toupper_inplace(b);
	return (b);
}

char			*convert_int(char *b, long long int v, t_printf_spec *s)
{
	ft_itoa_buf(b, v, 10);
	if (s->flags & PRINTF_PLUS && v >= 0)
		prepend_str(b, "+");
	else if (s->flags & PRINTF_SPACE && v >= 0)
		prepend_str(b, " ");
	if (v < 0 || (s->flags & (PRINTF_SPACE | PRINTF_PLUS)))
		s->prefix_w = 1;
	if (s->precision == 0 && !v && ft_strchr(b, '0'))
	{
		*ft_strchr(b, '0') = 0;
		return (b);
	}
	while (s->precision > (int)ft_strlen(b + s->prefix_w))
		prepend_str(b + s->prefix_w, "0");
	return (b);
}

char			*convert_double(char *b, long double v, t_printf_spec *s)
{
	ft_ftoa_buf(b, v, s->precision >= 0 ? s->precision : 6);
	if (s->flags & PRINTF_HASH && !s->precision)
		ft_strcat(b, ".");
	if (s->flags & PRINTF_PLUS && v >= 0)
		prepend_str(b, "+");
	else if (s->flags & PRINTF_SPACE && v >= 0)
		prepend_str(b, " ");
	if (v < 0 || (s->flags & (PRINTF_SPACE | PRINTF_PLUS)))
		s->prefix_w = 1;
	return (b);
}

int				convert_string(int fd, int ret, t_printf_spec s, char *str)
{
	size_t	len;
	char	fill_c;

	fill_c = ' ';
	if ((s.flags & PRINTF_ZERO) && MACOS)
		fill_c = '0';
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (s.precision >= 0 && s.precision < (int)len)
		len = s.precision;
	if (s.flags & PRINTF_MINUS)
	{
		ret += write(fd, str, len);
		while (s.field_width-- > len)
			ret += write(fd, &fill_c, 1);
	}
	else
	{
		while (s.field_width-- > len)
			ret += write(fd, &fill_c, 1);
		ret += write(fd, str, len);
	}
	return (ret);
}
