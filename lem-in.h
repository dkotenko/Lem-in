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

#endif