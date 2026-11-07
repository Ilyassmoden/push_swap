/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 06:44:17 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/07 07:07:32 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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

int	parse_input_bonus(int ac, char **av, t_list *a)
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
			if (!stack_push(a, s[j]))
				return (free_split(s), 0);
			j++;
		}
		free_split(s);
		i++;
	}
	return (1);
}
