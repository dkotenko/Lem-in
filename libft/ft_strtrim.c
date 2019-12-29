/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:27:45 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/10 14:24:01 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_spacesstr(void)
{
	char *result;

	result = (char *)malloc(1);
	result[0] = '\0';
	return (result);
}

char			*ft_strtrim(char const *s)
{
	char	*result;
	int		slen;
	int		i;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	if (*s == '\0')
		return (ft_spacesstr());
	slen = ft_strlen((char *)s);
	while (s[slen - 1] == ' ' || s[slen - 1] == '\n' || s[slen - 1] == '\t')
		slen--;
	result = (char *)malloc(sizeof(char) * slen + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
