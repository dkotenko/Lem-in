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

static int	is_line_informative(char *s)
{
	if (s[0] == '#')
	{
		if (s[1] != '#')
			return (0);
		else if (strcmp(s + 2, "start") && strcmp(s + 2, "end"))
			return (0);
	}
	return (1);
}

static void	ft_read_ants(int fd, t_input *input, t_array *arr)
{
	char	*s;

	s = NULL;
	get_next_line(fd, &s);
	while (!is_line_informative(s) && input->lines_counter++)
		get_next_line(fd, &s);
	is_valid_line(s, input, arr);
	t_input_write(s, input);
	arr->ants = ft_atoi(s);
	//ft_arr_malloc(arr); ARR НЕ ЗАМОЛОЧЕН
}

static void	ft_read_data(int fd, t_input *input, t_array *arr)
{
	char	*temp;
	char	**split;
	char 	flag;

	temp = NULL;
	ft_read_ants(fd, input, arr); //читает количество муравьёв
	while (get_next_line(fd, &temp))
	{
		if (!is_line_informative(temp) && (input->status != STATUS_IS_START &&
			input->status != STATUS_IS_END) && input->lines_counter++)
			continue ;
		input->prev_status = input->status;
		is_valid_line(temp, input, arr);
		split = (temp[0] == '#') ? NULL : ft_strsplit(temp, ' '); // если длина массива после сплита == 3 - то это комната, если 1 - то это связи		
		if (split && split[1] == NULL)
			ft_create_links(&arr, split, &input->ht->links); //создаём линки в комнатах
		else if (split && split[3] == NULL)
			ft_create_room(&arr, split, temp, input); //маллочим комнату, инициализируем переменные и закидываем её в общий массив всех комнат
		t_input_write(temp, input);
		ft_split_free(split);
	}
	if (input->status != STATUS_LINKS)
		handle_error("NO LINKS", input, arr);
}

void		ft_reader(int argc, char **argv, t_input *input, t_array *arr)
{
	int		fd;
	char 	*s;

	s = NULL;
	if (argc > 2)
		handle_error("args", input, arr);
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	if ((fd == -1 && handle_error("fd", input, arr)) ||
		(read(fd, s, 0) && handle_error("read", input, arr)))
		return ;
	ft_read_data(fd, input, arr); //читаем входные данные
}