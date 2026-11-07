/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rotationB.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-elm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:19:43 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/06 17:19:44 by iait-elm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/* Find the biggest number smaller than the given number in B.
 * إيجاد أكبر رقم أصغر من الرقم المعطى داخل B.
 */
static t_node	*find_best_target(t_stacks *stacks, int num)
{
	t_node	*j;
	t_node	*target;
	t_node	*max;

	j = stacks->b.head;
	target = NULL;
	while (j)
	{
		if (num > j->num && (!target || j->num > target->num))
			target = j;
		j = j->next;
	}
	if (!target)
	{
		j = stacks->b.head;
		max = j;
		while (j)
		{
			if (j->num > max->num)
				max = j;
			j = j->next;
		}
		target = max;
	}
	return (target);
}

/* Find the target in B for every node in A.
 * إيجاد Target لكل عنصر في A داخل B.
 */
void	find_target(t_stacks *stacks)
{
	t_node	*i;
	t_node	*target;

	if (!stacks->a.head || !stacks->b.head)
		return ;
	i = stacks->a.head;
	while (i)
	{
		target = find_best_target(stacks, i->num);
		i->target_index = target->index;
		i = i->next;
	}
}

/* Find the smallest number bigger than the given number in A.
 * إيجاد أصغر رقم أكبر من الرقم المعطى داخل A.
 */
static t_node	*find_next_bigger(t_stacks *stacks, int num)
{
	t_node	*j;
	t_node	*target;

	j = stacks->a.head;
	target = NULL;
	while (j)
	{
		if (j->num > num && (!target || j->num < target->num))
			target = j;
		j = j->next;
	}
	return (target);
}

/* Find the smallest node in A.
 * إيجاد أصغر عنصر في A.
 */
static t_node	*find_min_node(t_stacks *stacks)
{
	t_node	*j;
	t_node	*min;

	j = stacks->a.head;
	if (!j)
		return (NULL);
	min = j;
	while (j)
	{
		if (j->num < min->num)
			min = j;
		j = j->next;
	}
	return (min);
}

/* Find the target in A for every node in B.
 * إيجاد Target لكل عنصر في B داخل A.
 */
void	find_target_b_to_a(t_stacks *stacks)
{
	t_node	*i;
	t_node	*target;

	if (!stacks->a.head || !stacks->b.head)
		return ;
	i = stacks->b.head;
	while (i)
	{
		target = find_next_bigger(stacks, i->num);
		if (!target)
			target = find_min_node(stacks);
		i->target_index = target->index;
		i = i->next;
	}
}
