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

void	rotate_ra(t_list *stakA, size_t ops[RRR + 1])
{
	t_node	*tmp;

	if (!stakA || !stakA->head || !stakA->head->next)
		return ;
	tmp = stakA->head;
	stakA->head = stakA->head->next;
	tmp->next = NULL;
	stakA->tail->next = tmp;
	stakA->tail = tmp;
	ops[RA]++; 
	write(1, "ra\n", 3);
}

void	rotate_rb(t_list *stakB, size_t ops[RRR + 1])
{
	t_node	*tmp;

	if (!stakB || !stakB->head || !stakB->head->next)
		return ;
	tmp = stakB->head;
	stakB->head = stakB->head->next;
	tmp->next = NULL;
	stakB->tail->next = tmp;
	stakB->tail = tmp;
	ops[RB]++;
	write(1, "rb\n", 3);
}

void	rotate_rr(t_list *stakA, t_list *stakB, size_t ops[RRR + 1])
{
	t_node	*tmp;

	if (stakA && stakA->head && stakA->head->next)
	{
		tmp = stakA->head;
		stakA->head = stakA->head->next;
		tmp->next = NULL;
		stakA->tail->next = tmp;
		stakA->tail = tmp;
	}
	if (stakB && stakB->head && stakB->head->next)
	{
		tmp = stakB->head;
		stakB->head = stakB->head->next;
		tmp->next = NULL;
		stakB->tail->next = tmp;
		stakB->tail = tmp;
	}
	ops[RR]++;
	write(1, "rr\n", 3);
}
