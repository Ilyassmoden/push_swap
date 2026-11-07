/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 09:05:47 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/07 08:58:19 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	push_list(t_list *a, t_list *b)
{
	t_node	*second;

	if (!a->size)
		return ;
	second = a->head->next;
	ft_lstadd_front(b, a->head);
	a->head = second;
	if (second)
		second->prev = NULL;
	else
		a->tail = second;
	a->size--;
}

void	push(t_stacks *stacks, int op_idx, int silent)
{
	if (op_idx == PA_IDX)
		push_list(&stacks->b, &stacks->a);
	else if (op_idx == PB_IDX)
		push_list(&stacks->a, &stacks->b);
	if (silent)
		return ;
	stacks->ops[op_idx].count++;
	ft_putstr_fd(1, stacks->ops[op_idx].label);
	ft_putstr_fd(1, "\n");
}
