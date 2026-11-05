#include "../push_swap.h"

void	sort_array(int *arr, int size)
{
	int	a;
	int	b;
	int	temp;

	a = 0;
	while (a < size - 1)
	{
		b = a + 1;
		while (b < size)
		{
			if (arr[b] < arr[a])
			{
				temp = arr[b];
				arr[b] = arr[a];
				arr[a] = temp;
			}
			b++;
		}
		a++;
	}
}

void	index_stack(t_node *head, int size)
{
	int		*arr;
	t_node	*i;
	int		j;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		return ;
	i = head;
	j = 0;
	while (i)
	{
		arr[j++] = i->num;
		i = i->next;
	}
	sort_array(arr, size);
	i = head;
	while (i)
	{
		j = 0;
		while (j < size && i->num != arr[j])
			j++;
		i->index = j;
		i = i->next;
	}
	free(arr);
}

int	get_chunk_size(int size)
{
	if (size <= 100)
		return (20); 
	else
		return (45);
}

static int	get_max_index(t_list *a)
{
	t_node	*curr;
	int		max_val;
	int		min_idx;
	int		i;

	curr = a->head;
	max_val = curr->num;
	min_idx = 0;
	i = 0;
	while (curr)
	{
		if (curr->num > max_val)
		{
			max_val = curr->num;
			min_idx = i;
		}
		i++;
		curr = curr->next;
	}
	return (min_idx);
}
void	s(t_list *a, t_list *b, size_t ops[11])
{
	int	size;
	int	min_idx;

	while (b->head)
	{
		size = get_stack_size(b);
		min_idx = get_max_index(b);
		if (min_idx <= size / 2)
		{
			while (min_idx > 0)
			{
				rotate_rb(b, ops);
				min_idx--;
			}
		}
		else
		{
			min_idx = size - min_idx;
			while (min_idx > 0)
			{
				rotate_rrb(b, ops);
				min_idx--;
			}
		}
		push_pa(b, a, ops);
	}
}

void	push_chunk_to_b(t_list *a, t_list *b, int min, int max, size_t ops[11])
{
	int		i;
	t_node	*curr;

	while (1)
	{
		i = 0;
		curr = a->head;
		while (curr && (curr->index < min || curr->index >= max))
		{
			i++;
			curr = curr->next;
		}
		if (!curr)
			break ;
		if (i <= a->size / 2)
			while (i-- > 0)
				rotate_ra(a, ops);
		else
			while (i++ < a->size)
				rotate_rra(a, ops);
		push_pb(b, a, ops);
	}
}
void	push_a_to_b(t_list *a, t_list *b, int size, int size_chunk, size_t ops[11])
{
	int	min_chunk;
	int	max_chunk;

	min_chunk = 0;
	max_chunk = size_chunk;
	while (a->head)
	{
		if (max_chunk > size)
			max_chunk = size;
		push_chunk_to_b(a, b, min_chunk, max_chunk, ops);
		min_chunk = max_chunk;
		max_chunk += size_chunk;
	}
}
void	medium(t_list *a, t_list *b, size_t ops[11])
{
	int	size;
	int	size_chunk;

	size = get_stack_size(a);
	a->size = size;
	index_stack(a->head, size);
	size_chunk = get_chunk_size(size);
	
	// المرحلة 3: نقل جميع الكتل (شاملة الباقي) من A إلى B
	push_a_to_b(a, b, size, size_chunk, ops);
	s(a,b,ops);
	// المرحلة 4: إعادة العناصر من B إلى A مرتبة
}