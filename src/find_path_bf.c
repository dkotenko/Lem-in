#include "../includes/lem-in.h"
#include "../libft/libft.h"

void 	ft_malloc_bf_matrix(t_array **arr, int ***matrix, int ***path_mtrx)
{
	int i;

	i = 0;
	*matrix = (int**)malloc(sizeof(int*) * ((*arr)->current - 1));
	*path_mtrx = (int**)malloc(sizeof(int*) * ((*arr)->current - 1));
	while (i < (*arr)->current - 1)
	{
		(*matrix)[i] = (int*)malloc(sizeof(int) * (*arr)->current);
		(*path_mtrx)[i] = (int*)malloc(sizeof(int) * (*arr)->current);
		ft_fill_mem((*matrix)[i], (*arr)->current, INT_MAX);
		ft_fill_mem((*path_mtrx)[i], (*arr)->current, -1);
		i++;
	}

}

void 	ft_free_bf_matrix(t_array **arr, int **matrix, int **path_mtrx)
{
	int i;

	i = 0;
	while (i < (*arr)->current - 1)
	{
		free(matrix[i]);
		free(path_mtrx[i]);
		i++;
	}
	free(matrix);
	free(path_mtrx);
}

void	ft_fill_1st_line(t_array **arr, int **matrix, int **path)
{
	int k;

	k = 0;
	matrix[0][(*arr)->start] = 0;
	path[0][(*arr)->start] = (*arr)->start;
	while (k < (*arr)->rooms[(*arr)->start]->s_lnk.cur_size)
	{
		matrix[0][(*arr)->rooms[(*arr)->start]->s_lnk.links[k]] = (*arr)->rooms[(*arr)->start]->s_lnk.weights[k];
		path[0][(*arr)->rooms[(*arr)->start]->s_lnk.links[k]] = (*arr)->start;
		k++;
	}
}

void	ft_find_path_cycle(t_array **arr, int **matrix, int **path_mtrx, int i)
{
	int j;
	int k;

	j = 0;
	while (j < (*arr)->current)
	{
		if (matrix[i - 1][j] == INT_MAX && j++)
			continue;
		k = 0;
		matrix[i][j] = matrix[i - 1][j];
		path_mtrx[i][j] = path_mtrx[i - 1][j];
		while (k < (*arr)->rooms[j]->s_lnk.cur_size)
		{
			if ((*arr)->rooms[j]->s_lnk.weights[k] != -2)
				if (matrix[i][(*arr)->rooms[j]->s_lnk.links[k]] > matrix[i - 1][j] + 1)
				{
					matrix[i][(*arr)->rooms[j]->s_lnk.links[k]] = matrix[i - 1][j] + 1;
					path_mtrx[i][(*arr)->rooms[j]->s_lnk.links[k]] = j;
				}
			k++;
		}
		j++;
	}
}

t_path	*ft_restore_path_bf(t_array **arr, int **path_mtrx)
{
	t_path *path;
	int i;
	int j;
	int k;

	path = (t_path *)malloc(sizeof(t_path));
	path->path = (int*)malloc(sizeof(int) * (*arr)->current - 1);
	ft_fill_mem(path->path, (*arr)->current - 1, -1);
	i = (*arr)->current - 2;
	j = (*arr)->finish;
	k = 1;
	path->path[0] = (*arr)->finish;
	while (path_mtrx[i][j] != (*arr)->start && j != -1)
	{
		path->path[k] = path_mtrx[i][j];
		k++;
		j = path_mtrx[i][j];
		i--;
	}
	path->path[k] = (*arr)->start;
	path->order = 1;
	path->size = k + 1;
	path->curr_size = k + 1;
	return (j != -1 ? path : NULL);
}

t_path	*ft_find_path_bf(t_array **arr, int i)
{
	int	**matrix;
	int **path_mtrx;
	t_path	*path;

	ft_malloc_bf_matrix(arr, &matrix, &path_mtrx);
	ft_fill_1st_line(arr, matrix, path_mtrx);
	while (i < (*arr)->current - 1)
	{
		ft_find_path_cycle(arr, matrix, path_mtrx, i);
		i++;
	}
	path = ft_restore_path_bf(arr, path_mtrx);
	ft_free_bf_matrix(arr, matrix, path_mtrx);
	return (path);
}