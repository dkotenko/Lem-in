/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:17:43 by edrowzee          #+#    #+#             */
/*   Updated: 2020/02/12 14:17:44 by edrowzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_LEMIN_H
# define LEMIN_LEMIN_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include "t_htable.h"

# define ARR_INIT_SIZE 1024
# define STATUS_ANTS 1
# define STATUS_BEFORE_START 2
# define STATUS_IS_START 4
# define STATUS_BEFORE_END 8
# define STATUS_IS_END 16
# define STATUS_AFTER_END 32
# define STATUS_LINKS 64

typedef struct		s_links
{
	int				*links;
	int				*weights;
	int				room_copy;
	int				is_copy;
	int				max_size;
	int				cur_size;
}					t_links;

typedef struct		s_room
{
	char			*name;
	t_links			s_lnk;
	int				order;
	int				src;
	int				x;
	int				y;

}					t_room;

typedef struct		s_array
{
	int				max;
	int				current;
	int				base;
	int				start;
	int				finish;
	int				ants;
	t_room			**rooms;

}					t_array;

typedef struct		s_ant
{
	char			*name;
	int				path;
	int				order;
	int				position;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_path
{
	int				size;
	int				*path;
	int				curr_size;
	int				order;
}					t_path;

typedef struct		s_paths
{
	int				curr_path;
	int				paths_lim;
	t_path			**path_arr;
	int				time;
}					t_paths;

typedef struct		s_deleted_edges
{
	int				*edge_indexes;
	int				*edge_rooms;
	int				curr_size;
	int				size;
}					t_deleted_edges;

typedef struct		s_htables
{
	t_htable		*names;
	t_htable		*coords;
	t_htable		*links;

}					t_htables;

typedef struct		s_input
{
	int				current;
	char			**rows;
	int				status;
	int				prev_status;
	int				max;
	int				lines_counter;
	t_htables		*ht;
}					t_input;

void				print_t_links(t_links *s_lnk, t_array *arr);
void				print_t_array_rooms_with_links(t_array *arr);
void				print_t_path(t_path *path, t_array *arr);
void				print_t_paths(t_paths *paths, t_array *arr);
void				print_path(t_paths *paths, t_array *arr);
void				ft_print_bf_matrix(int **matrix, int **path, t_array **arr);
int					ft_split_free(char **split);
t_room				**ft_rooms_copy(t_room **rooms, int size);
void				ft_arr_malloc(t_array **arr);
int					*ft_int_arr_realloc(int *arr, int new_size);
void				ft_links_push(t_links *s_lnk, int push, int weight);
void				ft_arr_push(t_array **arr, t_room *room);
void				ft_create_room(t_array **arr, char **split, char *s,
					t_input *input);
void				ft_cpy_room_data(t_room *dst, t_room *src, int ds, int sr);
void				ft_create_links(t_array **arr, char **split,
					t_htable **ht_links);
void				ft_paths_sort(t_paths *paths);
void				ft_path_sort(t_path *path);
t_paths				*create_t_paths();
int					*copy_int_array(int *arr, int size);
t_path				*copy_t_path(t_path *path);
t_paths				*copy_t_paths(t_paths *paths);
t_array				*t_array_copy(t_array *arr);
t_room				*copy_room_mod(t_room **rooms, int i);
int					room_in_no_expanded(t_array *arr_not_expanded,
					t_room *room);
int					get_origin_room(int room_nb, t_array *arr);
int					nbr_in_array_pos(int number, int *arr, int size);
int					nbr_in_links_pos(t_array *arr, int curr, int link);
void				add_path_to_no_expanded(t_array *arr_not_expanded,
					t_array *arr, t_path *path);
void				delete_double_links(t_array *arr);
void				delete_edges_bf(t_array *arr, t_path *path,
					t_deleted_edges *edges);
t_deleted_edges		*t_deleted_edges_create(int size);
void				restore_edges_bf(t_array *arr, t_deleted_edges *edges);
void				t_deleted_edges_free(t_deleted_edges **edges);
void				handle_paths(t_array *arr_not_expanded, t_array *arr,
					t_paths *paths);
void				ft_reader(int argc, char **argv, t_input *input,
					t_array *arr);
int					ft_free(void *val);
int					merge_paths(t_array *arr, t_paths *paths);
int					t_path_has_duplicates(t_path *path);
void				t_array_free(t_array *arr);
void				t_paths_free(t_paths *paths);
void				t_path_free(t_path *path);
t_path				*t_path_create(int size);
int					is_valid_line(char *s, t_input *in, t_array *arr);
int					is_valid_room(char *s, t_input *input, t_array *arr);
int					handle_error(char *s, t_input *input, t_array *arr);
int					is_valid_link(char *s, t_input *input, t_array *arr);
void				ft_reader(int argc, char **argv, t_input *input,
					t_array *arr);
size_t				ft_ilen(int n);
void				t_room_free(t_room *room);
void				t_htables_init(t_input *input, int size,
					t_htable_cmp *cmp, t_htable_hash *hash);
void				t_htables_free(t_htables *ht);
void				t_input_malloc(t_input **input);
char				**t_input_rows_copy(char **rows, int size);
void				t_input_write(char *s, t_input *input);
void				t_input_print(t_input *input);
void				t_input_free(t_input *input);
t_path				*ft_find_path_dfs(t_array **arr, int j, int k);
t_path				*find_path_bf_new(t_array **arr);
t_ant				*ft_ants_creator();
void				ft_ants_parade(t_array **arr, t_ant *ants, t_paths *paths);
void				ft_list_sort(t_ant *ants);
void				ft_ants_prepare_to_parade(t_array **arr, t_paths *paths,
					int i);
void				ft_fill_mem(int *arr, int size, int num);
void				curr_size_to_size(t_paths *paths);
int					ft_calc_path_time(t_array **arr, t_paths *paths,
					int i, int j);
void				reset_order_src(t_array **arr);
void				ft_delete_room(t_room *room);
void				ft_reset_graph(t_array **arr);
void				ft_replace_cpy_in_path(t_array **arr, t_path *path);
void				ft_expand_graph(t_array **arr, int *path, int size);

#endif
