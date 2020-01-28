#include "../includes/lem-in.h"
#include "../libft/libft.h"

static t_path	*create_t_path(t_array **arr, int i)
{
	t_path *result;

	result = (t_path *)malloc(sizeof(t_path));
	result->path = (int*)malloc(sizeof(int) * ((*arr)->current + 1));
	ft_fill_mem(result->path, (*arr)->current + 1, -1);
	result->path[0] = (*arr)->start;
	result->path[1] = (*arr)->rooms[(*arr)->start]->s_lnk.links[i];
	result->size = 0;
	result->order = 1;
	return (result);
}

static void		modify_t_path(t_array **arr, t_path **path)
{
	t_path *result;

	result = *path;
	while (result->path[result->size] != (*arr)->finish)
		result->size++;
	result->size++;
	result->curr_size = result->size;
}

t_path			*ft_find_path_dfs(t_array **arr)
{
	t_path		*result;
	static int	i = -1;
	int			j;
	int			k;

	if (i == -1)
		i = (*arr)->rooms[(*arr)->start]->s_lnk.cur_size - 1;
	result = create_t_path(arr, i);
	j = 1;
	while (result->path[j] != (*arr)->finish)
	{
		k = -1;
		while (++k < (*arr)->rooms[result->path[j]]->s_lnk.cur_size)
		{
			if ((*arr)->rooms[result->path[j]]->s_lnk.weights[k] != -2)
			{
				j++;
				result->path[j] = (*arr)->rooms[result->path[j - 1]]->s_lnk.links[k];
				break;
			}
		}
	}
	i--;
	modify_t_path(arr, &result);
	ft_path_sort(result);
	return (result);
}