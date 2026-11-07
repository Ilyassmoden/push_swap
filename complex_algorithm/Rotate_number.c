/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rotationB.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-elm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:19:43 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/06 17:19:44 by iait-elm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	rotate_while(int count, t_stacks *stacks, int op_idx,
		int reverse)
{
	while (count > 0)
	{
		if (reverse)
			rrotate(stacks, op_idx, 0);
		else
			rotate(stacks, op_idx, 0);
		count--;
	}
}

void	rotate_num(int count, char *s, t_stacks *st)
{
	if (ft_strcmp(s, "rra") == 0)
		rotate_while(count, st, RRA_IDX, 1);
	else if (ft_strcmp(s, "rrb") == 0)
		rotate_while(count, st, RRB_IDX, 1);
	else if (ft_strcmp(s, "ra") == 0)
		rotate_while(count, st, RA_IDX, 0);
	else if (ft_strcmp(s, "rb") == 0)
		rotate_while(count, st, RB_IDX, 0);
	else if (ft_strcmp(s, "rr") == 0)
		rotate_while(count, st, RR_IDX, 0);
	else if (ft_strcmp(s, "rrr") == 0)
		rotate_while(count, st, RRR_IDX, 1);
}

/* Put the smallest element at the top of A.
 * وضع أصغر عنصر في أعلى Stack A.
 */

void	final_rotate(t_stacks *stacks)
{
	t_node	*current;
	t_node	*min;
	int		index;
	int		size;

	if (!stacks->a.head)
		return ;
	assign_index(stacks);
	current = stacks->a.head;
	min = current;
	while (current)
	{
		if (current->num < min->num)
			min = current;
		current = current->next;
	}
	index = min->index;
	size = stacks->a.size;
	if (index <= size / 2)
		rotate_num(index, "ra", stacks);
	else
		rotate_num(size - index, "rra", stacks);
}

void	calculate_cost_b_to_a(t_stacks *stacks)
{
	t_node	*node;

	if (!stacks->a.head || !stacks->b.head)
		return ;
	node = stacks->b.head;
	while (node)
	{
		calc_node_cost(node, stacks->b.size, stacks->a.size);
		node = node->next;
	}
}

t_node	*find_cheapest_b(t_stacks *stacks)
{
	t_node	*min;
	t_node	*node;

	if (!stacks->b.head)
		return (NULL);
	min = stacks->b.head;
	node = stacks->b.head->next;
	while (node)
	{
		if (node->total_cost < min->total_cost)
			min = node;
		node = node->next;
	}
	return (min);
}
