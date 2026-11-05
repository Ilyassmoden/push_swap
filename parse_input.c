/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 19:52:31 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/04 05:57:13 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	set_flag(int flags[BENCH_IDX + 1], const char *arg)
{
	if (flags[SIMPLE_IDX] || flags[MEDIUM_IDX]
		|| flags[COMPLEX_IDX] || flags[ADAPTIVE_IDX])
		return (0);
	if (!ft_strcmp(SIMPLE_FLAG, arg))
		return (flags[SIMPLE_IDX] = 1);
	if (!ft_strcmp(MEDIUM_FLAG, arg))
		return (flags[MEDIUM_IDX] = 1);
	if (!ft_strcmp(COMPLEX_FLAG, arg))
		return (flags[COMPLEX_IDX] = 1);
	if (!ft_strcmp(ADAPTIVE_FLAG, arg))
		return (flags[ADAPTIVE_IDX] = 1);
	if (!ft_strcmp(BENCH_FLAG, arg) && !flags[BENCH_IDX])
		return (flags[BENCH_IDX] = 1);
	return (0);
}

static int	stack_push(t_list *a, const char *arg)
{
	int		num;
	t_node	*node;

	if (!ft_atoi(arg, &num))
		return (0);
	node = a->head;
	while (node && node->num != num)
		node = node->next;
	if (node)
		return (0);
	node = ft_lstnew(num);
	if (!node)
		return (0);
	ft_lstadd_back(a, node);
	return (1);
}

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	parse_input(int ac, char **av, t_list *a, int flags[BENCH_IDX + 1])
{
	int		i;
	int		j;
	char	**s;

	i = 0;
	while (i < ac)
	{
		j = 0;
		s = ft_split(av[i], ' ');
		if (!s || !*s)
			return (0);
		while (s[j])
		{
			if (!a->head && set_flag(flags, s[j]))
				;
			else if (!stack_push(a, s[j]))
				return (free_split(s), 0);
			j++;
		}
		free_split(s);
		i++;
	}
	return (1);
}
