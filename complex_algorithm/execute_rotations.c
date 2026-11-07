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

/* Execute rotations when both costs have the same sign.
 * تنفيذ الدوران المشترك عندما تكون إشارتا التكلفة متشابهتين.
 */
void	execute_same_sign(t_stacks *stacks, t_node *cheapest)
{
	int		min;
	char	*str;

	min = ft_min(ft_abs(cheapest->cost_a),
			ft_abs(cheapest->cost_b));
	if (cheapest->cost_a < 0)
		rotate_num(min, "rrr", stacks);
	else
		rotate_num(min, "rr", stacks);
	if (ft_abs(cheapest->cost_a) > min)
	{
		str = "ra";
		if (cheapest->cost_a < 0)
			str = "rra";
		rotate_num(ft_abs(cheapest->cost_a) - min, str, stacks);
	}
	if (ft_abs(cheapest->cost_b) > min)
	{
		str = "rb";
		if (cheapest->cost_b < 0)
			str = "rrb";
		rotate_num(ft_abs(cheapest->cost_b) - min, str, stacks);
	}
}

/* Execute all rotations needed to move the cheapest node.
 * تنفيذ جميع الدورانات اللازمة لتحريك العنصر الأرخص.
 */
void	execute_rotations(t_stacks *stacks, t_node *cheapest)
{
	if (!cheapest)
		return ;
	if ((cheapest->cost_a < 0 && cheapest->cost_b < 0)
		|| (cheapest->cost_a > 0 && cheapest->cost_b > 0))
		execute_same_sign(stacks, cheapest);
	else
	{
		if (cheapest->cost_a < 0)
			rotate_num(ft_abs(cheapest->cost_a), "rra", stacks);
		else if (cheapest->cost_a > 0)
			rotate_num(cheapest->cost_a, "ra", stacks);
		if (cheapest->cost_b < 0)
			rotate_num(ft_abs(cheapest->cost_b), "rrb", stacks);
		else if (cheapest->cost_b > 0)
			rotate_num(cheapest->cost_b, "rb", stacks);
	}
}

/* Move the cheapest node from A to B.
 * نقل العنصر الأرخص من A إلى B.
 */
void	execute_moves(t_stacks *stacks, t_node *cheapest)
{
	if (!cheapest)
		return ;
	execute_rotations(stacks, cheapest);
	push(stacks, PB_IDX, 0);
}
