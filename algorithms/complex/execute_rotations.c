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

#include "../../push_swap.h"

/* Execute rotations when both costs have the same sign.
- تنفيذ الدوران المشترك عندما تكون إشارتا التكلفة متشابهتين.
 */
void	execute_same_sign(t_list *a, t_list *b,
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
		str = "ra";
		if (c->cost_a < 0)
			str = "rra";
		rotate_num(ft_abs(c->cost_a) - min, str, &st);
	}
	else
	{
		str = "rb";
		if (c->cost_b < 0)
			str = "rrb";
		rotate_num(ft_abs(c->cost_b) - min, str, &st);
	}
	(void)a;
	(void)b;
}

/* Execute all rotations needed to move the cheapest node.
- تنفيذ جميع الدورانات اللازمة لتحريك العنصر الأرخص.
 */
void	execute_rotations(t_list *a, t_list *b,
		t_node *cheapest, size_t ops[11])
{
	t_stacks	st;

	st.a = a;
	st.b = b;
	st.ops = ops;
	if ((cheapest->cost_a < 0 && cheapest->cost_b < 0)
		|| (cheapest->cost_a > 0 && cheapest->cost_b > 0))
		execute_same_sign(a, b, cheapest, ops);
	else
	{
		if (cheapest->cost_a < 0)
			rotate_num(ft_abs(cheapest->cost_a), "rra", &st);
		else if (cheapest->cost_a > 0)
			rotate_num(cheapest->cost_a, "ra", &st);
		if (cheapest->cost_b < 0)
			rotate_num(ft_abs(cheapest->cost_b), "rrb", &st);
		else if (cheapest->cost_b > 0)
			rotate_num(cheapest->cost_b, "rb", &st);
	}
}

/* Move the cheapest node from A to B.
- نقل العنصر الأرخص من A إلى B.
 */
void	execute_moves(t_list *a, t_list *b,
		t_node *cheapest, size_t ops[11])
{
	if (!cheapest)
		return ;
	execute_rotations(a, b, cheapest, ops);
	push_pb(b, a, ops);
}
