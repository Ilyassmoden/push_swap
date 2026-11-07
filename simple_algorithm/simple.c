/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 02:53:58 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/07 09:20:39 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static size_t	min_node(t_list list)
{
	t_node	*min;
	size_t	i;

	if (!list.head)
		return (0);
	min = list.head;
	i = 0;
	while (list.head)
	{
		list.head->index = i;
		if (list.head->num < min->num)
			min = list.head;
		list.head = list.head->next;
		i++;
	}
	return (min->index);
}

static void	move_top(t_stacks *stacks, size_t index)
{
	size_t	rotates;
	int		op_idx;
	void	(*op)(t_stacks *, int, int);

	if (index <= stacks->a.size / 2)
	{
		rotates = index;
		op_idx = RA_IDX;
		op = rotate;
	}
	else
	{
		rotates = stacks->a.size - index;
		op_idx = RRA_IDX;
		op = rrotate;
	}
	while (rotates--)
		op(stacks, op_idx, 0);
}

void	simple(t_stacks *stacks)
{
	while (stacks->a.size)
	{
		move_top(stacks, min_node(stacks->a));
		push(stacks, PB_IDX, 0);
	}
	while (stacks->b.size)
		push(stacks, PA_IDX, 0);
}
