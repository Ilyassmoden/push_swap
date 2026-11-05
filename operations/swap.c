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

void    swap_sa(t_node *a, t_node *b, size_t ops[RRR + 1])
{
    int tmp;

    (void)b;
    if (!a || !a->next)
        return ;
    tmp = a->num;
    a->num = a->next->num;
    a->next->num = tmp;
    ops[SA]++;
    write(1, "sa\n", 3);
}

void    swap_sb(t_node *a, t_node *b, size_t ops[RRR + 1])
{
    int tmp;

    (void)a;
    if (!b || !b->next)
        return ;
    tmp = b->num;
    b->num = b->next->num;
    b->next->num = tmp;
    ops[SB]++;
    write(1, "sb\n", 3);
}

void	swap_ss(t_list *stack_a, t_list *stack_b, size_t ops[RRR + 1])
{
	int	tmp;

	if (stack_a && stack_a->head && stack_a->head->next)
	{
		tmp = stack_a->head->num;
		stack_a->head->num = stack_a->head->next->num;
		stack_a->head->next->num = tmp;
	}
	if (stack_b && stack_b->head && stack_b->head->next)
	{
		tmp = stack_b->head->num;
		stack_b->head->num = stack_b->head->next->num;
		stack_b->head->next->num = tmp;
	}
	ops[SS]++;
	write(1, "ss\n", 3);
}
