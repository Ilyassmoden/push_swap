/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-elm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:21:15 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/07 16:21:16 by iait-elm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	find_max_position(t_list *stack)
{
	t_node	*current;
	int		max_value;
	int		max_position;
	int		position;

	current = stack->head;
	max_value = current->num;
	max_position = 0;
	position = 0;
	while (current)
	{
		if (current->num > max_value)
		{
			max_value = current->num;
			max_position = position;
		}
		position++;
		current = current->next;
	}
	return (max_position);
}

static void	return_sorted_to_a(t_stacks *stacks)
{
	int	size;
	int	max_position;

	while (stacks->b.head)
	{
		size = get_stack_size(&stacks->b);
		max_position = find_max_position(&stacks->b);
		if (max_position <= size / 2)
		{
			while (max_position-- > 0)
				rotate(stacks, RB_IDX, 0);
		}
		else
		{
			max_position = size - max_position;
			while (max_position-- > 0)
				rrotate(stacks, RRB_IDX, 0);
		}
		push(stacks, PA_IDX, 0);
	}
}

static void	push_current_chunk(t_stacks *stacks, int min, int max)
{
	unsigned int	position;
	t_node			*current;

	while (1)
	{
		position = 0;
		current = stacks->a.head;
		while (current && (current->index < min
				|| current->index >= max))
		{
			position++;
			current = current->next;
		}
		if (!current)
			break ;
		if (position <= stacks->a.size / 2)
			while (position-- > 0)
				rotate(stacks, RA_IDX, 0);
		else
			while (position++ < stacks->a.size)
				rrotate(stacks, RRA_IDX, 0);
		push(stacks, PB_IDX, 0);
	}
}

static void	push_all_chunks_to_b(t_stacks *stacks, int size,
		int chunk_size)
{
	int	min_chunk;
	int	max_chunk;

	min_chunk = 0;
	max_chunk = chunk_size;
	while (stacks->a.head)
	{
		if (max_chunk > size)
			max_chunk = size;
		push_current_chunk(stacks, min_chunk, max_chunk);
		min_chunk = max_chunk;
		max_chunk += chunk_size;
	}
}

void	chunk_sort(t_stacks *stacks)
{
	int	size;
	int	chunk_size;

	size = get_stack_size(&stacks->a);
	if (size <= 1)
		return ;
	stacks->a.size = size;
	index_stack(stacks->a.head, size);
	chunk_size = get_chunk_size(size);
	push_all_chunks_to_b(stacks, size, chunk_size);
	return_sorted_to_a(stacks);
}
