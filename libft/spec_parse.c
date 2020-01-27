/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:22:26 by edrowzee          #+#    #+#             */
/*   Updated: 2019/10/16 12:29:49 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft_compat.h"

static int		parse_field_width(char **s)
{
	int r;

	r = 0;
	if (**s != '0' && ft_isdigit(**s))
	{
		r = (10 * r) + (**s - '0');
		(*s)++;
	}
	while (ft_isdigit(**s))
	{
		r = (10 * r) + (**s - '0');
		(*s)++;
	}
	return (r);
}

static uint		parse_flags(char **s)
{
	uint flags;

	flags = 0;
	while (**s && ft_strchr("#0+- ", **s))
	{
		if (**s == '#')
			flags |= PRINTF_HASH;
		else if (**s == '0')
			flags |= PRINTF_ZERO;
		else if (**s == '-')
			flags |= PRINTF_MINUS;
		else if (**s == '+')
			flags |= PRINTF_PLUS;
		else if (**s == ' ')
			flags |= PRINTF_SPACE;
		(*s)++;
	}
	return (flags);
}

static char		parse_format(char *modifiers, char **s)
{
	int i;

	i = 0;
	while (**s && ft_strchr("lhL", **s))
	{
		if (i < 2)
			*modifiers++ = **s;
		i++;
		(*s)++;
	}
	if (**s && ft_strchr("diouxXscpf%", **s))
	{
		*modifiers = 0;
		return (*(*s)++);
	}
	*modifiers = 0;
	return (0);
}

static int		parse_precision(char **s)
{
	int r;

	r = 0;
	if (**s != '.')
		return (-1);
	else
		(*s)++;
	while (ft_isdigit(**s))
	{
		r *= 10;
		r += **s - '0';
		(*s)++;
	}
	return (r);
}

t_printf_spec	parse_printf_spec(char **ptr)
{
	t_printf_spec spec;

	(*ptr)++;
	spec.prefix_w = 0;
	spec.flags = parse_flags(ptr);
	spec.field_width = parse_field_width(ptr);
	spec.precision = parse_precision(ptr);
	spec.type = parse_format(spec.modifiers, ptr);
	return (spec);
}
