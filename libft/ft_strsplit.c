/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 12:58:47 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/10 14:25:09 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char		**ft_memfree(char **res, int i)
{
	while (i >= 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
	return (NULL);
}

static int		ft_strlenc(char const *s, char c)
{
	int len_str;

	len_str = 0;
	while (*s != c)
	{
		if (*s == '\0')
			break ;
		len_str++;
		s++;
	}
	return (len_str);
}

static char		*ft_strdupc(const char *src, char c)
{
	int		i;
	char	*result;

	i = 0;
	result = (char*)malloc(sizeof(char) * ft_strlenc(src, c) + 1);
	if (result == NULL)
		return (NULL);
	while (src[i] != c && src[i] != '\0')
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int		ft_count_words(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			counter++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (counter);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		num_words;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	num_words = ft_count_words(s, c);
	if ((res = (char **)malloc(sizeof(char *) * (num_words + 1))) == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s != c)
		{
			if ((res[i] = ft_strdupc(s, c)) == NULL)
				return (ft_memfree(res, i));
			s = s + ft_strlenc(res[i], '\0');
			i++;
		}
		else
			s++;
	}
	res[i] = NULL;
	return (res);
}
