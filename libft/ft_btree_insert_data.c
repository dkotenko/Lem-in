/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:07:45 by edrowzee          #+#    #+#             */
/*   Updated: 2019/06/21 20:06:48 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_insert_data(t_btree **root, void *item,
		int (*cmpf)(void *, void *))
{
	if (*root == 0)
		*root = ft_btree_create_node(item);
	else if (cmpf((*root)->item, item) > 0)
		ft_btree_insert_data(&(*root)->left, item, cmpf);
	else if (cmpf((*root)->item, item) <= 0)
		ft_btree_insert_data(&(*root)->right, item, cmpf);
}
