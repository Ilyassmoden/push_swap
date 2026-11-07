/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 22:31:55 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/07 07:16:06 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	print_bench_strategy(int *flags, float disorder)
{
	ft_putstr_fd(2, "\n[bench] strategy:  ");
	if (flags[SIMPLE_IDX])
		ft_putstr_fd(2, "Simple / O(n^2)\n");
	else if (flags[MEDIUM_IDX])
		ft_putstr_fd(2, "Medium / O(n√n)\n");
	else if (flags[COMPLEX_IDX])
		ft_putstr_fd(2, "Complex / O(n log n)\n");
	else if (disorder <= 0.2)
		ft_putstr_fd(2, "Adaptive / O(n^2)\n");
	else if (disorder > 0.2 && disorder <= 0.5)
		ft_putstr_fd(2, "Adaptive / O(n√n)\n");
	else
		ft_putstr_fd(2, "Adaptive / O(n log n)\n");
}

static void	print_bench_ops_part1(t_stacks stacks)
{
	ft_putstr_fd(2, "\n[bench] ");
	ft_putstr_fd(2, stacks.ops[SA_IDX].label);
	ft_putstr_fd(2, "  :  ");
	ft_putnbr_fd(2, stacks.ops[SA_IDX].count);
	ft_putstr_fd(2, "  ");
	ft_putstr_fd(2, stacks.ops[SB_IDX].label);
	ft_putstr_fd(2, ":  ");
	ft_putnbr_fd(2, stacks.ops[SB_IDX].count);
	ft_putstr_fd(2, "  ");
	ft_putstr_fd(2, stacks.ops[SS_IDX].label);
	ft_putstr_fd(2, ":  ");
	ft_putnbr_fd(2, stacks.ops[SS_IDX].count);
	ft_putstr_fd(2, "  ");
	ft_putstr_fd(2, stacks.ops[PA_IDX].label);
	ft_putstr_fd(2, ":  ");
	ft_putnbr_fd(2, stacks.ops[PA_IDX].count);
	ft_putstr_fd(2, "  ");
	ft_putstr_fd(2, stacks.ops[PB_IDX].label);
	ft_putstr_fd(2, ":  ");
	ft_putnbr_fd(2, stacks.ops[PB_IDX].count);
}

static void	print_bench_ops_part2(t_stacks stacks)
{
	ft_putstr_fd(2, "\n[bench] ");
	ft_putstr_fd(2, stacks.ops[RA_IDX].label);
	ft_putstr_fd(2, "  :  ");
	ft_putnbr_fd(2, stacks.ops[RA_IDX].count);
	ft_putstr_fd(2, "  ");
	ft_putstr_fd(2, stacks.ops[RB_IDX].label);
	ft_putstr_fd(2, ":  ");
	ft_putnbr_fd(2, stacks.ops[RB_IDX].count);
	ft_putstr_fd(2, "  ");
	ft_putstr_fd(2, stacks.ops[RR_IDX].label);
	ft_putstr_fd(2, ":  ");
	ft_putnbr_fd(2, stacks.ops[RR_IDX].count);
	ft_putstr_fd(2, "  ");
	ft_putstr_fd(2, stacks.ops[RRA_IDX].label);
	ft_putstr_fd(2, ":  ");
	ft_putnbr_fd(2, stacks.ops[RRA_IDX].count);
	ft_putstr_fd(2, "  ");
	ft_putstr_fd(2, stacks.ops[RRB_IDX].label);
	ft_putstr_fd(2, ":  ");
	ft_putnbr_fd(2, stacks.ops[RRB_IDX].count);
	ft_putstr_fd(2, "  ");
	ft_putstr_fd(2, stacks.ops[RRR_IDX].label);
	ft_putstr_fd(2, ":  ");
	ft_putnbr_fd(2, stacks.ops[RRR_IDX].count);
}

void	print_bench(t_stacks stacks, int *flags, float disorder)
{
	int		vel;
	int		i;
	size_t	total;

	i = 0;
	total = 0;
	ft_putstr_fd(2, "[bench] disorder:  ");
	ft_putnbr_fd(2, (int)(disorder * 100 + 0.5));
	ft_putstr_fd(2, ".");
	vel = (int)(disorder * 1000 + 0.5);
	ft_putnbr_fd(2, vel % 10);
	vel = (int)(disorder * 10000 + 0.5);
	ft_putnbr_fd(2, vel % 10);
	ft_putstr_fd(2, "%");
	print_bench_strategy(flags, disorder);
	ft_putstr_fd(2, "[bench] total_ops:  ");
	while (i <= RRR_IDX)
		total += stacks.ops[i++].count;
	ft_putnbr_fd(2, (int)total);
	print_bench_ops_part1(stacks);
	print_bench_ops_part2(stacks);
	ft_putstr_fd(2, "\n");
}
