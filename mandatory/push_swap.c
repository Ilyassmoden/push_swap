/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 19:15:34 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/07 07:47:57 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	init_ops(t_op *ops)
{
	ops[SA_IDX].label = SA;
	ops[SB_IDX].label = SB;
	ops[SS_IDX].label = SS;
	ops[PA_IDX].label = PA;
	ops[PB_IDX].label = PB;
	ops[RA_IDX].label = RA;
	ops[RB_IDX].label = RB;
	ops[RR_IDX].label = RR;
	ops[RRA_IDX].label = RRA;
	ops[RRB_IDX].label = RRB;
	ops[RRR_IDX].label = RRR;
}

static float	compute_disorder(t_list a)
{
	t_node	*i;
	t_node	*j;
	float	mistakes;
	float	total_pairs;

	if (a.size < 2)
		return (0);
	mistakes = 0;
	total_pairs = 0;
	i = a.head;
	while (i && i->next)
	{
		j = i->next;
		while (j)
		{
			if (i->num > j->num)
				mistakes++;
			total_pairs++;
			j = j->next;
		}
		i = i->next;
	}
	return (mistakes / total_pairs);
}

static void	print_algorithm(t_stacks *stacks, int *flags, float disorder)
{
	if (flags[SIMPLE_IDX])
		simple(stacks);
	else if (flags[MEDIUM_IDX])
		medium(stacks);
	else if (flags[COMPLEX_IDX])
		complex(stacks);
	else if (disorder < 0.2)
		simple(stacks);
	else if (disorder < 0.5 && disorder > 0.2)
		medium(stacks);
	else
		complex(stacks);
}

int	main(int ac, char **av)
{
	t_stacks	stacks;
	int			flags[BENCH_IDX + 1];
	float		disorder;

	ft_bzero(&stacks, sizeof(t_stacks));
	ft_bzero(flags, sizeof(flags));
	init_ops(stacks.ops);
	if (ac < 2)
		return (0);
	if (!parse_input(ac - 1, &av[1], &stacks.a, flags))
	{
		ft_lstclear(&stacks.a);
		ft_putstr_fd(2, "Error\n");
		return (1);
	}
	disorder = compute_disorder(stacks.a);
	if (disorder)
		print_algorithm(&stacks, flags, disorder);
	if (flags[BENCH_IDX])
		print_bench(stacks, flags, disorder);
	ft_lstclear(&stacks.a);
	ft_lstclear(&stacks.b);
	return (0);
}
