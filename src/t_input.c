#include "../includes/lem-in.h"

void			t_input_print(t_input *input)
{
	int			i;

	i = -1;
	while (++i < input->current)
	{
		ft_putstr(input->rows[i]);
		ft_putchar('\n');
		//ft_printf("%s\n", input->rows[i]);
	}
}

void			t_input_write(char *s, t_input *input)
{
	if (input->current == input->max)
		t_input_malloc(&input);
	input->rows[input->current] = s;
	input->current++;
	input->lines_counter++;
}

void			t_input_malloc(t_input **input)
{
	static int	size = ARR_INIT_SIZE;

	if (*input == NULL)
	{
		*input = (t_input *)malloc(sizeof(t_input) * 1);
		(*input)->rows = (char **)malloc(sizeof(char *) * size);
		(*input)->current = 0;
		(*input)->lines_counter = 1;
		(*input)->status = STATUS_ANTS;
		(*input)->max = size;
		(*input)->ht = (t_htables *)malloc(sizeof(t_htables));
		t_htables_init(*input, INIT_PRIME_NUMBER, &cmp_func, &hash_func);
	}
	if ((*input)->current == (*input)->max)
	{
		size *= 2;
		(*input)->rows = t_input_rows_copy((*input)->rows, (*input)->max);
		(*input)->max *= 2;
	}
	return ;
}

char		**t_input_rows_copy(char **rows, int size)
{
	int		i;
	char	**new_rows;

	i = 0;
	new_rows = (char **)malloc(sizeof(char *) * size * 2);
	while (i < size)
	{
		new_rows[i] = rows[i];
		i++;
	}
	free(rows);
	return (new_rows);
}

void	t_input_free(t_input *input)
{	
	t_htables_free(input->ht);
	while (--(input->current) > -1)
		free(input->rows[input->current]);
	free(input->rows);
	free(input);	
}
