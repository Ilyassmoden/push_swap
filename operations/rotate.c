/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 09:05:47 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/07 08:58:33 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	rotate_list(t_list *a)
{
	t_node	*old_head;

	if (!a || a->size < 2)
		return ;
	old_head = a->head;
	a->head = old_head->next;
	a->head->prev = NULL;
	old_head->next = NULL;
	old_head->prev = a->tail;
	a->tail->next = old_head;
	a->tail = old_head;
}

void	rotate(t_stacks *stacks, int op_idx, int silent)
{
	if (op_idx == RA_IDX)
		rotate_list(&stacks->a);
	else if (op_idx == RB_IDX)
		rotate_list(&stacks->b);
	else if (op_idx == RR_IDX)
	{
		rotate_list(&stacks->a);
		rotate_list(&stacks->b);
	}
	if (silent)
		return ;
	stacks->ops[op_idx].count++;
	ft_putstr_fd(1, stacks->ops[op_idx].label);
	ft_putstr_fd(1, "\n");
}
