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

static void	execute_same_sign_b(t_stacks *stacks, t_node *cheapest)
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
		str = "rb";
		if (cheapest->cost_a < 0)
			str = "rrb";
		rotate_num(ft_abs(cheapest->cost_a) - min, str, stacks);
	}
	if (ft_abs(cheapest->cost_b) > min)
	{
		str = "ra";
		if (cheapest->cost_b < 0)
			str = "rra";
		rotate_num(ft_abs(cheapest->cost_b) - min, str, stacks);
	}
}

static void	execute_rotations_b(t_stacks *stacks, t_node *cheapest)
{
	if ((cheapest->cost_a < 0 && cheapest->cost_b < 0)
		|| (cheapest->cost_a > 0 && cheapest->cost_b > 0))
		execute_same_sign_b(stacks, cheapest);
	else
	{
		if (cheapest->cost_a < 0)
			rotate_num(ft_abs(cheapest->cost_a), "rrb", stacks);
		else if (cheapest->cost_a > 0)
			rotate_num(cheapest->cost_a, "rb", stacks);
		if (cheapest->cost_b < 0)
			rotate_num(ft_abs(cheapest->cost_b), "rra", stacks);
		else if (cheapest->cost_b > 0)
			rotate_num(cheapest->cost_b, "ra", stacks);
	}
}

void	execute_moves_b(t_stacks *stacks, t_node *cheapest)
{
	if (!cheapest)
		return ;
	execute_rotations_b(stacks, cheapest);
	push(stacks, PA_IDX, 0);
}
