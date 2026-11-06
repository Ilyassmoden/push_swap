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

#include "../../push_swap.h"

/* Helper function to find the best target in B.
 */
static t_node	*find_best_target(t_list *b, int i_num)
{
	t_node	*j;
	t_node	*target;
	t_node	*max;

	j = b->head;
	target = NULL;
	while (j)
	{
		if (i_num > j->num && (!target || j->num > target->num))
			target = j;
		j = j->next;
	}
	if (!target)
	{
		j = b->head;
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

/* Find the target node in stack B for every node in A.
- إيجاد أكبر عنصر أصغر من كل عنصر في A داخل B.
 */
void	find_target(t_list *a, t_list *b)
{
	t_node	*i;

	if (!a || !b || !b->head)
		return ;
	i = a->head;
	while (i)
	{
		i->target_index = find_best_target(b, i->num)->index;
		i = i->next;
	}
}

/* Find the correct target in A and move the cheapest node from B.
- إيجاد المكان المناسب في A ثم نقل العنصر الأرخص من B.
 */
t_node	*find_next_bigger(t_list *a, int num)
{
	t_node	*j;
	t_node	*target;

	j = a->head;
	target = NULL;
	while (j)
	{
		if (j->num > num && (!target || j->num < target->num))
			target = j;
		j = j->next;
	}
	return (target);
}

t_node	*find_min_node(t_list *a)
{
	t_node	*j;
	t_node	*min;

	j = a->head;
	min = j;
	while (j)
	{
		if (j->num < min->num)
			min = j;
		j = j->next;
	}
	return (min);
}

void	find_target_b_to_a(t_list *b, t_list *a)
{
	t_node	*i;
	t_node	*target;

	if (!a || !a->head || !b)
		return ;
	i = b->head;
	while (i)
	{
		target = find_next_bigger(a, i->num);
		if (!target)
			target = find_min_node(a);
		i->target_index = target->index;
		i = i->next;
	}
}

/* Put the smallest element at the top of stack A.
- وضع أصغر عنصر في أعلى Stack A.
 */
void	final_rotate(t_list *a, size_t ops[11])
{
	t_node		*current;
	int			min;
	int			index;
	int			size;
	t_stacks	st;

	if (!a || !a->head)
		return ;
	assign_index(a, NULL);
	current = a->head;
	min = current->num;
	index = current->index;
	size = get_stack_size(a);
	while (current)
	{
		if (current->num < min)
		{
			min = current->num;
			index = current->index;
		}
		current = current->next;
	}
	st.a = a;
	st.b = NULL;
	st.ops = ops;
	if (index <= size / 2)
		rotate_num(index, "ra", &st);
	else
		rotate_num(size - index, "rra", &st);
}