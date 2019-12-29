/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:19:22 by edrowzee          #+#    #+#             */
/*   Updated: 2019/09/07 18:32:52 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*start_list;

	if (!lst || !f)
		return (NULL);
	if (!(start_list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	start_list = f(lst);
	start_list->next = ft_lstmap(lst->next, f);
	return (start_list);
}
