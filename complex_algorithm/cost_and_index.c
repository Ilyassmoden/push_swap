/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rotations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-elm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:26:38 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/06 17:26:39 by iait-elm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/* Set the current position of every node.
 * حساب position ديال كل node.
 */
static void	set_indices(t_node *node)
{
	int	p;

	p = 0;
	while (node)
	{
		node->index = p++;
		node = node->next;
	}
}

/* Assign positions to both stacks.
 * تحديد المواقع الحالية للعناصر في A و B.
 */
void	assign_index(t_stacks *stacks)
{
	set_indices(stacks->a.head);
	set_indices(stacks->b.head);
}

/* Calculate movement cost for one node.
 * حساب تكلفة تحريك node والـ target ديالو.
 */
void	calc_node_cost(t_node *node, int size_a, int size_b)
{
	if (size_a / 2 < node->index)
		node->cost_a = (size_a - node->index) * -1;
	else
		node->cost_a = node->index;
	if (size_b / 2 < node->target_index)
		node->cost_b = (size_b - node->target_index) * -1;
	else
		node->cost_b = node->target_index;
	if ((node->cost_a < 0 && node->cost_b < 0)
		|| (node->cost_a > 0 && node->cost_b > 0))
		node->total_cost = ft_max(ft_abs(node->cost_a),
				ft_abs(node->cost_b));
	else
		node->total_cost = ft_abs(node->cost_a)
			+ ft_abs(node->cost_b);
}

/* Calculate costs for all nodes in A.
 * حساب تكلفة جميع العناصر الموجودة في A.
 */
void	calculate_cost(t_stacks *stacks)
{
	t_node	*node;

	if (!stacks->a.head || !stacks->b.head)
		return ;
	node = stacks->a.head;
	while (node)
	{
		calc_node_cost(node, stacks->a.size, stacks->b.size);
		node = node->next;
	}
}

/* Find the node with the lowest movement cost.
 * إيجاد العنصر الأقل تكلفة.
 */
t_node	*find_cheapest(t_stacks *stacks)
{
	t_node	*min;
	t_node	*node;

	if (!stacks->a.head)
		return (NULL);
	min = stacks->a.head;
	node = stacks->a.head->next;
	while (node)
	{
		if (node->total_cost < min->total_cost)
			min = node;
		node = node->next;
	}
	return (min);
}
