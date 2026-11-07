/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 09:05:47 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/07 08:58:56 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	rrotate_list(t_list *list)
{
	t_node	*old_tail;

	if (!list || list->size < 2)
		return ;
	old_tail = list->tail;
	list->tail = old_tail->prev;
	list->tail->next = NULL;
	old_tail->prev = NULL;
	old_tail->next = list->head;
	list->head->prev = old_tail;
	list->head = old_tail;
}

void	rrotate(t_stacks *stacks, int op_idx, int silent)
{
	if (op_idx == RRA_IDX)
		rrotate_list(&stacks->a);
	else if (op_idx == RRB_IDX)
		rrotate_list(&stacks->b);
	else if (op_idx == RRR_IDX)
	{
		rrotate_list(&stacks->a);
		rrotate_list(&stacks->b);
	}
	if (silent)
		return ;
	stacks->ops[op_idx].count++;
	ft_putstr_fd(1, stacks->ops[op_idx].label);
	ft_putstr_fd(1, "\n");
}
