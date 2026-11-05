/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 19:15:34 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/03 23:46:55 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
int	main(int ac, char **av)
{
	t_list	a;
	t_list	b;
	int		flags[BENCH_IDX + 1];

	ft_bzero(&a, sizeof(t_list));
	ft_bzero(&b, sizeof(t_list));
	ft_bzero(flags, sizeof(flags));
	if (ac < 2)
		return (0);
	if (!parse_input(ac - 1, &av[1], &a, flags))
	{
		ft_lstclear(&a);
		ft_putstr_fd(2, "Error\n");
		return (1);
	}
	print_algorithm(&a, &b, flags);
	ft_lstclear(&a);
	return (0);
}
