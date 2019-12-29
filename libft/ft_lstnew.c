/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:47:30 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/07 17:49:54 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *result;

	result = (t_list *)malloc(sizeof(t_list));
	if (result == NULL)
		return (NULL);
	result->next = NULL;
	if (content == NULL)
	{
		result->content = NULL;
		result->content_size = 0;
	}
	else
	{
		result->content = malloc(content_size);
		if (result->content == NULL)
		{
			free(result);
			return (NULL);
		}
		ft_memmove(result->content, content, content_size);
		result->content_size = content_size;
	}
	return (result);
}
