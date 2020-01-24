#include "../includes/lem-in.h"
#include "../libft/libft.h"

t_path	*ft_find_path_dfs(t_array **arr)
{
	t_path		*result;
	static int	i = -1;
	int			j;
	int			k;

	if (i == -1)
		i = (*arr)->rooms[(*arr)->start]->s_lnk.cur_size - 1;
	result = (t_path *)malloc(sizeof(t_path));
	result->path = (int*)malloc(sizeof(int) * ((*arr)->current + 1));
	ft_fill_mem(result->path, (*arr)->current + 1, -1);

	result->path[0] = (*arr)->start;
	result->path[1] = (*arr)->rooms[(*arr)->start]->s_lnk.links[i];
	j = 1;
	while (result->path[j] != (*arr)->finish)
	{
		k = 0;
		while (k < (*arr)->rooms[result->path[j]]->s_lnk.cur_size)
		{
			if ((*arr)->rooms[result->path[j]]->s_lnk.weights[k] != -2)
			{
				j++;
				result->path[j] = (*arr)->rooms[result->path[j - 1]]->s_lnk.links[k];
				break;
			}
			k++;
		}
	}
	result->size = 0;
	while (result->path[result->size] != (*arr)->finish)
		result->size++;
	result->size++;
	result->curr_size = result->size;
	result->order = 1;
	i--;
	ft_path_sort(result);
	return (result);
}