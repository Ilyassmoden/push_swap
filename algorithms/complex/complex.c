/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-elm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:16:09 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/06 17:16:10 by iait-elm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

static void	sort_small(t_list *a, size_t ops[11])
{
	if (get_stack_size(a) == 2)
	{
		if (a->head->num > a->head->next->num)
			swap_sa(a->head, NULL, ops);
	}
	else if (get_stack_size(a) == 3)
		sort_three(a, ops);
}

void	complex(t_list *a, t_list *b, size_t ops[11])
{
	int	size;

	size = get_stack_size(a);
	if (size <= 3)
	{
		sort_small(a, ops);
		return ;
	}
	push_pb(b, a, ops);
	push_pb(b, a, ops);
	sort_a_to_b(a, b, ops);
	sort_small(a, ops);
	sort_b_to_a(a, b, ops);
	final_rotate(a, ops);
}
