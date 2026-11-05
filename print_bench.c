/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-elm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 22:31:55 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/04 05:57:53 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_bench_strategy(int flags[BENCH_IDX + 1], float disorder)
{
	ft_putstr_fd(2, "\n[bench] strategy:  ");
	if (flags[SIMPLE_IDX])
		ft_putstr_fd(2, "Simple / O(N^2)\n");
	else if (flags[MEDIUM_IDX])
		ft_putstr_fd(2, "Medium / O(N√N)\n");
	else if (flags[COMPLEX_IDX])
		ft_putstr_fd(2, "Complex / O(N log N)\n");
	else if (disorder <= 0.2)
		ft_putstr_fd(2, "Adaptive / O(N^2)\n");
	else if (disorder > 0.2 && disorder <= 0.5)
		ft_putstr_fd(2, "Adaptive / O(N√N)\n");
	else
		ft_putstr_fd(2, "Adaptive / O(N log N)\n");
}

static void	print_bench_ops_part1(size_t ops[RRR + 1])
{
	ft_putstr_fd(2, "\n[bench] sa  :  ");
	ft_putnbr_fd(2, ops[SA]);
	ft_putstr_fd(2, "  sb:  ");
	ft_putnbr_fd(2, ops[SB]);
	ft_putstr_fd(2, "  ss:  ");
	ft_putnbr_fd(2, ops[SS]);
	ft_putstr_fd(2, "  pa:  ");
	ft_putnbr_fd(2, ops[PA]);
	ft_putstr_fd(2, "  pb:  ");
	ft_putnbr_fd(2, ops[PB]);
}

static void	print_bench_ops_part2(size_t ops[RRR + 1])
{
	ft_putstr_fd(2, "\n[bench] ra  :  ");
	ft_putnbr_fd(2, ops[RA]);
	ft_putstr_fd(2, "  rb:  ");
	ft_putnbr_fd(2, ops[RB]);
	ft_putstr_fd(2, "  rr:  ");
	ft_putnbr_fd(2, ops[RR]);
	ft_putstr_fd(2, "  rra:  ");
	ft_putnbr_fd(2, ops[RRA]);
	ft_putstr_fd(2, "  rrb:  ");
	ft_putnbr_fd(2, ops[RRB]);
	ft_putstr_fd(2, "  rrr:  ");
	ft_putnbr_fd(2, ops[RRR]);
}

void	print_bench(int flags[BENCH_IDX + 1],
		float disorder, size_t ops[RRR + 1])
{
	int	vel;
	int	i;

	i = 0;
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
	vel = 0;
	while (i <= RRR)
		vel += ops[i++];
	ft_putnbr_fd(2, vel);
	print_bench_ops_part1(ops);
	print_bench_ops_part2(ops);
	ft_putstr_fd(2, "\n");
}
