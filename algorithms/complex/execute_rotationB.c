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

#include "../../push_swap.h"

/* Move the cheapest node from B back to A.
- إعادة العنصر الأرخص من B إلى A.
 */
static void	execute_same_sign_b(t_list *a, t_list *b,
		t_node *c, size_t ops[11])
{
	int			min;
	char		*str;
	t_stacks	st;

	st.a = a;
	st.b = b;
	st.ops = ops;
	min = ft_min(ft_abs(c->cost_a), ft_abs(c->cost_b));
	if (c->cost_a < 0)
		rotate_num(min, "rrr", &st);
	else
		rotate_num(min, "rr", &st);
	if (ft_abs(c->cost_a) > ft_abs(c->cost_b))
	{
		str = "rb";
		if (c->cost_a < 0)
			str = "rrb";
		rotate_num(ft_abs(c->cost_a) - min, str, &st);
	}
	else
	{
		str = "ra";
		if (c->cost_b < 0)
			str = "rra";
		rotate_num(ft_abs(c->cost_b) - min, str, &st);
	}
	(void)a;
	(void)b;
}

static void	execute_rotations_b(t_list *a, t_list *b,
		t_node *c, size_t ops[11])
{
	t_stacks	st;

	st.a = a;
	st.b = b;
	st.ops = ops;
	if ((c->cost_a < 0 && c->cost_b < 0)
		|| (c->cost_a > 0 && c->cost_b > 0))
		execute_same_sign_b(a, b, c, ops);
	else
	{
		if (c->cost_a < 0)
			rotate_num(ft_abs(c->cost_a), "rrb", &st);
		else if (c->cost_a > 0)
			rotate_num(c->cost_a, "rb", &st);
		if (c->cost_b < 0)
			rotate_num(ft_abs(c->cost_b), "rra", &st);
		else if (c->cost_b > 0)
			rotate_num(c->cost_b, "ra", &st);
	}
}

void	execute_moves_b(t_list *a, t_list *b,
		t_node *cheapest, size_t ops[11])
{
	if (!cheapest)
		return ;
	execute_rotations_b(a, b, cheapest, ops);
	push_pa(b, a, ops);
}
