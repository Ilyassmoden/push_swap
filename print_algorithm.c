/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_algorithm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-elm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 19:23:05 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/04 06:15:48 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static float	comput_disorder(t_list *a)
{
	t_node	*i;
	t_node	*j;
	float	mistakes;
	float	total_pairs;

	if (!a || !a->head || !a->head->next)
		return (0);
	i = a->head;
	mistakes = 0;
	total_pairs = 0;
	while (i && i->next)
	{
		j = i->next;
		while (j)
		{
			total_pairs += 1;
			if (i->num > j->num)
				mistakes += 1;
			j = j->next;
		}
		i = i->next;
	}
	return (mistakes / total_pairs);
}

void	print_algorithm(t_list *a, t_list *b, int flags[BENCH_IDX + 1])
{
	float	disorder;
	size_t	ops[RRR + 1];

	ft_bzero(ops, sizeof(ops));
	disorder = comput_disorder(a);
	if (!disorder)
	{
		if (flags[BENCH_IDX])
			print_bench(flags, disorder, ops);
		return ;
	}
	if (flags[SIMPLE_IDX])
		simple(a, b, ops);
	else if (flags[MEDIUM_IDX])
		medium(a, b, ops);
	else if (flags[COMPLEX_IDX])
		complex(a, b, ops);
	else if (disorder < 0.2)
		simple(a, b, ops);
	else if (disorder < 0.5 && disorder > 0.2)
		medium(a, b, ops);
	else
		complex(a, b, ops);
	if (flags[BENCH_IDX])
		print_bench(flags, disorder, ops);
}
