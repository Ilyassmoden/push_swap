
#include "../push_swap.h"

int	get_stack_size(t_list *a)
{
	t_node	*curr;
	int		size;

	curr = a->head;
	size = 0;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

static int	get_min_index(t_list *a)
{
	t_node	*curr;
	int		min_val;
	int		min_idx;
	int		i;

	curr = a->head;
	min_val = curr->num;
	min_idx = 0;
	i = 0;
	while (curr)
	{
		if (curr->num < min_val)
		{
			min_val = curr->num;
			min_idx = i;
		}
		i++;
		curr = curr->next;
	}
	return (min_idx);
}

static int	is_sorted(t_list *a)
{
	t_node	*curr;

	curr = a->head;
	while (curr && curr->next)
	{
		if (curr->num > curr->next->num)
			return (0);
		curr = curr->next;
	}
	return (1);
}

static void	sort_three(t_list *a, size_t ops[11])
{
	int	first;
	int	second;
	int	third;

	first = a->head->num;
	second = a->head->next->num;
	third = a->tail->num;
	if (first > second && second < third && first < third)
		swap_sa(a->head, a->head->next, ops);
	else if (first > second && second > third)
	{
		swap_sa(a->head, a->head->next, ops);
		rotate_rra(a, ops);
	}
	else if (first > second && second < third && first > third)
		rotate_ra(a, ops);
	else if (first < second && second > third && first < third)
	{
		swap_sa(a->head, a->head->next, ops);
		rotate_ra(a, ops);
	}
	else if (first < second && second > third && first > third)
		rotate_rra(a, ops);
}

static void	bring_min_to_top(t_list *a, size_t ops[11])
{
	int	size;
	int	min_idx;
	int	i;

	size = get_stack_size(a);
	min_idx = get_min_index(a);
	if (min_idx <= size / 2)
	{
		i = 0;
		while (i++ < min_idx)
			rotate_ra(a, ops);
	}
	else
	{
		i = 0;
		while (i++ < size - min_idx)
			rotate_rra(a, ops);
	}
}

static void	sort_four(t_list *a, t_list *b, size_t ops[11])
{
	bring_min_to_top(a, ops);
	push_pb(b, a, ops);
	sort_three(a, ops);
	push_pa(b, a, ops);
}

static void	sort_five(t_list *a, t_list *b, size_t ops[11])
{
	bring_min_to_top(a, ops);
	push_pb(b, a, ops);
	bring_min_to_top(a, ops);
	push_pb(b, a, ops);
	sort_three(a, ops);
	push_pa(b, a, ops);
	push_pa(b, a, ops);
}

void	simple(t_list *a, t_list *b, size_t ops[11])
{
	int	size;

	size = get_stack_size(a);
	if (size <= 1 || is_sorted(a))
		return ;
	if (size == 2)
	{
		if (a->head->num > a->tail->num)
			swap_sa(a->head, a->head->next, ops);
	}
	else if (size == 3)
		sort_three(a, ops);
	else if (size == 4)
		sort_four(a, b, ops);
	else if (size == 5)
		sort_five(a, b, ops);
	else
	{
		while (a->head)
		{
			bring_min_to_top(a, ops);
			push_pb(b, a, ops);
		}
		while (b->head)
			push_pa(b, a, ops);
	}
}
