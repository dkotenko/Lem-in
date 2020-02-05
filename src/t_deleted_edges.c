#include "includes/lem-in.h"

t_deleted_edges	*t_deleted_edges_create(int size)
{
	t_deleted_edges *deleted_edges;

	deleted_edges = (t_deleted_edges *)malloc(sizeof(deleted_edges)	* size);
	deleted_edges->edge_indexes = (int *)malloc(sizeof(int)	* size);
	deleted_edges->edge_rooms = (int *)malloc(sizeof(int) * size);
	deleted_edges->curr_size = 0;
	deleted_edges->size = size;
	return (deleted_edges);
}

void	t_deleted_edges_free(t_deleted_edges **edges)
{
	free((*edges)->edge_indexes);
	free((*edges)->edge_rooms);
	free(*edges);
}

