/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 06:39:26 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/07 08:35:38 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	execute_op(t_stacks *stacks, char *op)
{
	if (!ft_strcmp(op, SA))
		return (swap(stacks, SA_IDX, 1), 1);
	if (!ft_strcmp(op, SB))
		return (swap(stacks, SB_IDX, 1), 1);
	if (!ft_strcmp(op, SS))
		return (swap(stacks, SS_IDX, 1), 1);
	if (!ft_strcmp(op, PA))
		return (push(stacks, PA_IDX, 1), 1);
	if (!ft_strcmp(op, PB))
		return (push(stacks, PB_IDX, 1), 1);
	if (!ft_strcmp(op, RA))
		return (rotate(stacks, RA_IDX, 1), 1);
	if (!ft_strcmp(op, RB))
		return (rotate(stacks, RB_IDX, 1), 1);
	if (!ft_strcmp(op, RR))
		return (rotate(stacks, RR_IDX, 1), 1);
	if (!ft_strcmp(op, RRA))
		return (rrotate(stacks, RRA_IDX, 1), 1);
	if (!ft_strcmp(op, RRB))
		return (rrotate(stacks, RRB_IDX, 1), 1);
	if (!ft_strcmp(op, RRR))
		return (rrotate(stacks, RRR_IDX, 1), 1);
	return (0);
}

static int	is_list_sorted(t_list list)
{
	while (list.head && list.head->next)
	{
		if (list.head->num > list.head->next->num)
			return (0);
		list.head = list.head->next;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_stacks	stacks;
	char		*op;

	ft_bzero(&stacks, sizeof(t_stacks));
	if (ac < 2)
		return (0);
	if (!parse_input_bonus(ac - 1, &av[1], &stacks.a))
		return (ft_lstclear(&stacks.a), ft_lstclear(&stacks.b),
			ft_putstr_fd(2, "Error\n"), 1);
	op = get_next_line(0);
	while (op && execute_op(&stacks, op))
	{
		free(op);
		op = get_next_line(0);
	}
	if (op)
		return (free(op), ft_lstclear(&stacks.a), ft_lstclear(&stacks.b),
			ft_putstr_fd(2, "Error\n"), 1);
	if (stacks.b.size || !is_list_sorted(stacks.a))
		return (ft_lstclear(&stacks.a), ft_lstclear(&stacks.b),
			ft_putstr_fd(1, "KO\n"), 1);
	return (ft_lstclear(&stacks.a), ft_lstclear(&stacks.b),
		ft_putstr_fd(1, "OK\n"), 0);
}
