/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:35:02 by edrowzee          #+#    #+#             */
/*   Updated: 2019/06/20 20:03:33 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*ft_btree_create_node(void *item)
{
	t_btree *result;

	result = (t_btree*)malloc(sizeof(t_btree));
	if (result == 0)
		return (0);
	result->item = item;
	result->left = 0;
	result->right = 0;
	return (result);
}
