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

/* Sort exactly three elements in ascending order. */
static void	sort_three_cases(t_stacks *stacks, int first,
		int second, int third)
{
	if (first > second && second > third)
	{
		swap(stacks, SA_IDX, 0);
		rotate_num(1, "rra", stacks);
	}
	else if (first > second && first > third)
		rotate_num(1, "ra", stacks);
	else if (second > third && first < third)
	{
		swap(stacks, SA_IDX, 0);
		rotate_num(1, "ra", stacks);
	}
	else if (second > third)
		rotate_num(1, "rra", stacks);
	else if (first > second)
		swap(stacks, SA_IDX, 0);
}

void	sort_three(t_stacks *stacks)
{
	int	first;
	int	second;
	int	third;

	if (!stacks || !stacks->a.head || !stacks->a.head->next
		|| !stacks->a.head->next->next)
		return ;
	first = stacks->a.head->num;
	second = stacks->a.head->next->num;
	third = stacks->a.head->next->next->num;
	sort_three_cases(stacks, first, second, third);
}

/* Move all elements from B back to A. */
void	sort_b_to_a(t_stacks *stacks)
{
	while (stacks->b.size > 0)
		find_target_b(stacks);
}

/* Find the cheapest element in B to move to A. */
void	find_target_b(t_stacks *stacks)
{
	t_node	*cheapest;

	if (!stacks || !stacks->a.head || !stacks->b.head)
		return ;
	assign_index(stacks);
	find_target_b_to_a(stacks);
	calculate_cost_b_to_a(stacks);
	cheapest = find_cheapest_b(stacks);
	execute_moves_b(stacks, cheapest);
}

/* Keep three elements in A and move the rest to B. */
void	sort_a_to_b(t_stacks *stacks)
{
	t_node	*cheapest;

	while (stacks->a.size > 3)
	{
		assign_index(stacks);
		find_target(stacks);
		calculate_cost(stacks);
		cheapest = find_cheapest(stacks);
		execute_moves(stacks, cheapest);
	}
}
