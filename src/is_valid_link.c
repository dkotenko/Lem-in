/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 13:39:55 by clala             #+#    #+#             */
/*   Updated: 2020/01/19 17:40:13 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static		int rooms_in_link_exists(char **splitted, t_input *input, t_array *arr)
{
	int hash_1room;
	int hash_2room;

	hash_1room = input->ht->names->hash(splitted[0], input->ht->names->size);
	hash_2room = input->ht->names->hash(splitted[1], input->ht->names->size);
	if (t_htable_find(hash_1room,splitted[0], input->ht->names) &&
			t_htable_find(hash_2room,splitted[1], input->ht->names))
		return (1);
	return (0);
	//ft_free2dchararr(&splitted, 2);
}

static void	check_links_are_unique(char *s, t_input *input, t_array *arr)
{
	char	*reverse;
	char	*hyphen;
	int		i;
	int		j;
	
	reverse = ft_strnew(ft_strlen(s));
	hyphen = ft_strchr(s, '-');
	i = -1;
	while (hyphen[1 + ++i])
		reverse[i] = hyphen[1 + i];
	reverse[i++] = '-';
	j = -1;
	while (s[++j] != '-')
		reverse[i++] = s[j];
	if (t_htable_find(input->ht->links->hash(s, input->ht->links->size),
		s, input->ht->links))
		handle_error("Link already exists", input, arr);

	if (t_htable_find(input->ht->links->hash(reverse, input->ht->links->size),
		reverse, input->ht->links))
		handle_error("Reverse link exists", input, arr);
}

void		check_link_name(char *s, t_input *input, t_array *arr)
{
	int		i;

	i = -1;
	while(s[++i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '-' && s[i] != '_')
			handle_error("Invalid character in link", input, arr);
	}
}

int			is_valid_link(char *s, t_input *input, t_array *arr)
{
	char	**splitted;
	char	*hyphen;

	if (!(hyphen = ft_strchr(s, '-')) || ft_strchr(hyphen + 1, '-'))
		handle_error("Invalid link ", input, arr);
	check_link_name(s, input, arr);
	splitted = ft_strsplit(s, '-');
	if (!ft_strlen(splitted[0]) || !ft_strlen(splitted[1]))
		handle_error("Invalid link ", input, arr);
	if (!ft_strcmp(splitted[0], splitted[1]))
		handle_error("Link refers to the same room", input, arr);
	if (!rooms_in_link_exists(splitted, input, arr))
		handle_error("Room(s) in link do(es)n`t exist", input, arr);
	check_links_are_unique(s, input, arr);
	//ft_free2dchararr(&splitted, 2);
	return (1);
}
