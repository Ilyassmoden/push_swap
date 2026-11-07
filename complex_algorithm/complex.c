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

static void	sort_small(t_stacks *stacks)
{
	if (stacks->a.size == 2)
	{
		if (stacks->a.head->num > stacks->a.head->next->num)
			swap(stacks, SA_IDX, 0);
	}
	else if (stacks->a.size == 3)
		sort_three(stacks);
}

void	complex(t_stacks *stacks)
{
	if (stacks->a.size <= 3)
	{
		sort_small(stacks);
		return ;
	}
	push(stacks, PB_IDX, 0);
	push(stacks, PB_IDX, 0);
	sort_a_to_b(stacks);
	sort_small(stacks);
	sort_b_to_a(stacks);
	final_rotate(stacks);
}
