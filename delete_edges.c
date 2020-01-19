void delete_edges_bf(t_array *arr, t_path *path, t_deleted_edges *edges)
{
	int 	index_next;
	int 	i;

	i = -1;
	while (++i + 1 < path->size)
	{
		index_next = nbr_in_array_pos(path->path[i + 1],
									  arr->rooms[path->path[i]]->s_lnk.links,
									  arr->rooms[path->path[i]]->s_lnk.cur_size);
		arr->rooms[path->path[i]]->s_lnk.weights[index_next] = -2;
		edges->edge_rooms[edges->curr_size] = path->path[i];
		edges->edge_indexes[edges->curr_size] = index_next;
		edges->curr_size++;
	}
}