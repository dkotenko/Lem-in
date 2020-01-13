#ifndef LEMIN_LEM_IN_H
# define LEMIN_LEM_IN_H

# include <stdlib.h>
# include <stdio.h>
//# include <io.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# define ARR_INIT_SIZE 2

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
	int		x; //координата Х (для визуализации)
	int		y; //координата Y (для визуализации)

}				t_room;

typedef struct	s_array
{
	int		max; //сколько указателей выделено под комнаты
	int		current; //сколько указателей сейчас занято комнатами
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

#endif