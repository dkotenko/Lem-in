/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:16:53 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/18 14:20:36 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_check_for_line_end(char *result, char **fd_array, int *flag)
{
	while (*result != '\0')
	{
		if (*result == '\n')
		{
			*result = '\0';
			result++;
			if (*result != '\0')
				if ((*fd_array = ft_strdup(result)) == NULL)
				{
					flag[0] = -1;
					return (0);
				}
			return (1);
		}
		result++;
	}
	return (0);
}

static char		*ft_malloc_str(char *result, char *buf)
{
	char *temp;

	if (result == NULL)
	{
		if ((result = (char *)ft_memalloc(ft_strlen(buf) + 1)) == NULL)
			return (NULL);
		ft_strcpy(result, buf);
	}
	else
	{
		if ((temp = malloc(ft_strlen(result) + 1)) == NULL)
			return (NULL);
		ft_strcpy(temp, result);
		free(result);
		if ((result = ft_strjoin(temp, buf)) == NULL)
			return (NULL);
		free(temp);
	}
	return (result);
}

int				get_next_line(const int fd, char **line)
{
	static char	*fd_array[1025];
	char		buf[BUFF_SIZE + 1];
	int			read_size;
	int			flag[1];

	if ((flag[0] = 0) || fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	if (!(*line = NULL) && fd_array[fd] != NULL)
	{
		MALLCHECK((*line = ft_strdup(fd_array[fd])));
		free(fd_array[fd]);
		fd_array[fd] = NULL;
		if (ft_check_for_line_end(*line, &fd_array[fd], flag))
			return (1);
		MALLCKECK_INT(flag[0]);
	}
	while ((read_size = read(fd, buf, BUFF_SIZE)))
	{
		buf[read_size] = '\0';
		MALLCHECK((*line = ft_malloc_str(*line, buf)));
		if (ft_check_for_line_end(*line, &fd_array[fd], flag))
			return (1);
		MALLCKECK_INT(flag[0]);
	}
	return (read_size == 0 && fd_array[fd] == NULL && *line == NULL) ? 0 : 1;
}
