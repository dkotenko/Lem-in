/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:22:18 by edrowzee          #+#    #+#             */
/*   Updated: 2020/02/13 21:01:09 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"
#include "libft_compat.h"

int	ft_printf_ap(int fd, const char *format, va_list ap)
{
	char			*ptr;
	char			*ptr1;
	int				r;
	t_printf_spec	spec;

	r = 0;
	ptr = (char *)format;
	ptr1 = ptr;
	while ((ptr = ft_strchr(ptr, '%')))
	{
		r += write(fd, ptr1, ptr - ptr1);
		spec = parse_printf_spec(&ptr);
		if (spec.type)
			r += ft_printf_conversion(fd, (va_list*)(ap), spec);
		ptr1 = ptr;
	}
	r += ft_putstr_fd(ptr1, fd);
	return (r);
}

int	ft_printf(const char *format, ...)
{
	int		r;
	va_list	ap;

	va_start(ap, format);
	r = ft_printf_ap(1, format, ap);
	va_end(ap);
	return (r);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	int		r;
	va_list	ap;

	va_start(ap, format);
	r = ft_printf_ap(fd, format, ap);
	va_end(ap);
	return (r);
}
