#ifndef LEMIN_LEM_IN_H
# define LEMIN_LEM_IN_H

# include <stdlib.h>
# include <stdio.h>
//# include <io.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# define ARR_INIT_SIZE 10
# define PRIME_NUMBER 17

typedef struct	s_links
{
	int		*links; //сами связи - индекс комнаты в массиве
	int		*weights; //длина связи (по умолчанию 1, -1 для ревёрснутых путей, -2 для стёртых путей)
	int		order; // нужен для алгоритма в ширину(который сейчас не используется), в остальных местах не используется
	int		room_copy; //когда раздваиваем комнату в суурбале тут хранится индекс копии (а в копии соответственно индекс начальной)
	int		is_copy;
	int		max_size; //сколько памяти отмаллочено для линков
	int		cur_size; //сколько всего линков хранится в комнате
}				t_links;

typedef struct	s_room
{
	char	*name; //имя комнаты пришедшее во входных данных
	t_links	s_lnk; //связи комнаты
	int		flag; //
	int		order; // для BF
	int 	src; //с какой комнаты пришли
	int		x; //координата Х (для визуализации)
	int		y; //координата Y (для визуализации)

}				t_room;

typedef struct	s_array
{
	int		max; //сколько указателей выделено под комнаты
	int		current; //сколько указателей сейчас занято комнатами
	int		base; //изначальное количество комнат
	int		start; //стартовая комната в графе
	int		finish; //финишная комната в графе
	int		ants; //количество муравьёв
	t_room	**rooms; //массив указателей на комнаты

}				t_array;

typedef struct	s_ant
{
	char	*name;
	int     path;
    int				order;
    int				position;
    struct s_ant	*next;
}				t_ant;

typedef struct	s_path
{
	int 	size;
	int 	*path;
    int		curr_size;
    int		order;
}				t_path;

typedef struct	s_paths
{
	int 	curr_path;
	int		paths_lim;
	t_path	**path_arr;
	int		time;
}				t_paths;

typedef struct	s_deleted_edges
{
	int 		*edge_indexes;
	int 		*edge_rooms;
	int 		curr_size;
	int 		size;
}				t_deleted_edges;

//debug
void	print_t_links(t_links *s_lnk, t_array *arr);
void	print_t_array_rooms_with_links(t_array *arr);
void	print_t_path(t_path *path, t_array *arr);
void	print_t_paths(t_paths *paths, t_array *arr);
void	print_path(t_paths *paths, t_array *arr);
void	ft_print_bf_matrix(int **matrix, int **path, t_array **arr);

//read input
void	ft_split_free(char **split);
t_room	**ft_rooms_copy(t_room **rooms, int size);
void	ft_arr_malloc(t_array **arr);
int		*ft_int_arr_realloc(int *arr, int new_size);
void	ft_links_push(t_links *s_lnk, int push, int weight);
void	ft_arr_push(t_array **arr, t_room *room);
void	ft_read_ants(int fd, t_array **arr);
void	ft_create_room(t_array **arr, char **split, int *flag);
void	ft_cpy_room_data(t_room *dst, t_room *src, int ds, int sr);
void	ft_create_links(t_array **arr, char **split);
void	ft_read_data(int fd, t_array **arr);

//clala
void	ft_paths_sort(t_paths *paths);
void	ft_path_sort(t_path *path);
t_paths *create_t_paths();
int		*copy_int_array(int *arr, int size);
t_path *copy_t_path(t_path *path);
t_paths *copy_t_paths(t_paths *paths);
t_array *get_copy_t_array(t_array *arr);
t_room *copy_room_mod(t_room **rooms, int i);
int 	room_in_no_expanded(t_array *arr_not_expanded, t_room *room);
int     get_origin_room(int room_nb, t_array *arr);
int     nbr_in_array_pos(int number, int *arr, int size);
int     nbr_in_links_pos(t_array *arr , int curr, int link);
void	add_path_to_no_expanded(t_array *arr_not_expanded, t_array *arr, t_path *path);
void	delete_double_links(t_array *arr);
void	delete_edges_bf(t_array *arr, t_path *path, t_deleted_edges *edges);
t_deleted_edges	*create_deleted_edges(int size);
void	restore_edges_bf(t_array *arr, t_deleted_edges *edges);
void	free_t_path(t_path **path);
void	free_t_deleted_edges(t_deleted_edges **edges);
void	handle_paths(t_array *arr_not_expanded, t_array *arr, t_paths *paths);
void	ft_reader(int argc, char **argv, t_array **arr);
int		ft_free(void *val);
int			hash_table_add(int hash, int pointer, int *hash_table);
int		hash_func(char *s, int table_size);
int		ft_path_limit(t_array *arr);
int		merge_paths(t_array *arr, t_paths *paths);

//
void	ft_fill_mem(int *arr, int size, int num);

//find path dfs
t_path	*ft_find_path_dfs(t_array **arr);

//find path bfs
void	ft_check_for_cpy_bfs_smart(t_array **arr, t_path *path);
int		ft_find_best_room_bfs_smart(t_array **arr, int curr, int order);
t_path	*ft_restore_path_bfs_smart(t_array **arr);
int		ft_find_room_bfs(t_room *rooms, int *i, int *j, t_path *path);
t_path	*ft_restore_path_bfs(t_array **arr);
int		ft_find_recur_bfs(int *queue, int **cur_queue, t_array **arr);
t_path	*ft_find_path_bfs(t_array **arr);


//find path bf
void 	ft_malloc_bf_matrix(t_array **arr, int ***matrix, int ***path_mtrx);
void 	ft_free_bf_matrix(t_array **arr, int **matrix, int **path_mtrx);
void	ft_fill_1st_line(t_array **arr, int **matrix, int **path);
void	ft_find_path_cycle(t_array **arr, int **matrix, int **path_mtrx, int i);
t_path	*ft_restore_path_bf(t_array **arr, int **path_mtrx);
t_path	*ft_find_path_bf(t_array **arr, int i);

//ants
t_ant	*ft_ants_creator(int start_room);
void	ft_ant_reporting(char *name, char *room);
void	ft_ants_parade(t_array **arr, t_ant *ants, t_paths *paths);
void	ft_list_sort(t_ant *ants);
void	ft_ants_prepare_to_parade(t_array **arr, t_paths *paths);

//paths_tech
void	ft_fill_mem(int *arr, int size, int num);
void	curr_size_to_size(t_paths *paths);
int		ft_calc_path_time(t_array **arr, t_paths *paths);

//graph_tech
void	ft_clear_order(t_array **arr);
t_room	*ft_cpy_room(t_room *src); ///не должно использоваться в итоговом проекте
t_array *ft_cpy_graph(t_array *arr); ///не должно использоваться в итоговом проекте

//expand graph
void	ft_expand_graph(t_array **arr, int *path, int size);


#endif