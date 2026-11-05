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

void	rotate_rra(t_list *stakA, size_t ops[RRR + 1])
{
	t_node	*tmp;
	t_node	*last;

	if (!stakA || !stakA->head || !stakA->head->next)
		return ;
	tmp = stakA->head;
	last = stakA->head;
	while (last->next->next)
		last = last->next;
	stakA->head = last->next;
	last->next->next = tmp;
	last->next = NULL;
	stakA->tail = last;
	ops[RRA]++;
	write(1, "rra\n", 4);
}

void	rotate_rrb(t_list *stakB, size_t ops[RRR + 1])
{
	t_node	*tmp;
	t_node	*last;

	if (!stakB || !stakB->head || !stakB->head->next)
		return ;
	tmp = stakB->head;
	last = stakB->head;
	while (last->next->next)
		last = last->next;
	stakB->head = last->next;
	last->next->next = tmp;
	last->next = NULL;
	stakB->tail = last;
	ops[RRB]++;
	write(1, "rrb\n", 4);
}

static void	reverse_rotate(t_list *stack)
{
	t_node	*tmp;
	t_node	*last;

	if (!stack || !stack->head || !stack->head->next)
		return ;
	tmp = stack->head;
	last = stack->head;
	while (last->next->next)
		last = last->next;
	stack->head = last->next;
	last->next->next = tmp;
	last->next = NULL;
	stack->tail = last;
}

void	rotate_rrr(t_list *stakA, t_list *stakB, size_t ops[RRR + 1])
{
	reverse_rotate(stakA);
	reverse_rotate(stakB);
	ops[RRR]++;
	write(1, "rrr\n", 4);
}
