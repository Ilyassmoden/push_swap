/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-elm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 09:05:47 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/03 09:05:48 by iait-elm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push_pa(t_list *stackB, t_list *stackA, size_t ops[RRR + 1])
{
	t_node	*tmp;

	if (!stackB || !stackB->head)
		return ;
	tmp = stackB->head;
	stackB->head = stackB->head->next;
	if (!stackB->head)
		stackB->tail = NULL;
	if (!stackA->head)
	{
		stackA->head = tmp;
		stackA->tail = tmp;
		tmp->next = NULL;
	}
	else
	{
		tmp->next = stackA->head;
		stackA->head = tmp;
	}
	ops[PA]++;
	write(1, "pa\n", 3);
}

void	push_pb(t_list *stackB, t_list *stackA, size_t ops[RRR + 1])
{
	t_node	*tmp;

	if (!stackA || !stackA->head)
		return ;
	tmp = stackA->head;
	stackA->head = stackA->head->next;
	if (!stackA->head)
		stackA->tail = NULL;
	if (!stackB->head)
	{
		stackB->head = tmp;
		stackB->tail = tmp;
		tmp->next = NULL;
	}
	else
	{
		tmp->next = stackB->head;
		stackB->head = tmp;
	}
	ops[PB]++;
	write(1, "pb\n", 3);
}
