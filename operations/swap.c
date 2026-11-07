/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 09:05:47 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/07 08:59:06 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	swap_list(t_list *list)
{
	t_node	*first;
	t_node	*second;
	t_node	*third;

	if (!list || list->size < 2)
		return ;
	first = list->head;
	second = first->next;
	third = second->next;
	first->next = third;
	first->prev = second;
	second->next = first;
	second->prev = NULL;
	if (third)
		third->prev = first;
	else
		list->tail = first;
	list->head = second;
}

void	swap(t_stacks *stacks, int op_idx, int silent)
{
	if (op_idx == SA_IDX)
		swap_list(&stacks->a);
	else if (op_idx == SB_IDX)
		swap_list(&stacks->b);
	else if (op_idx == SS_IDX)
	{
		swap_list(&stacks->a);
		swap_list(&stacks->b);
	}
	if (silent)
		return ;
	stacks->ops[op_idx].count++;
	ft_putstr_fd(1, stacks->ops[op_idx].label);
	ft_putstr_fd(1, "\n");
}
