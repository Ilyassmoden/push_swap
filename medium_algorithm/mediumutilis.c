/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mediumutilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 07:18:47 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/07 16:20:14 by iait-elm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	get_stack_size(t_list *a)
{
	t_node	*curr;
	int		size;

	curr = a->head;
	size = 0;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

int	get_chunk_size(int size)
{
	if (size <= 100)
		return (20);
	else
		return (45);
}

void	index_stack(t_node *head, int size)
{
	int		*arr;
	t_node	*i;
	int		j;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		return ;
	i = head;
	j = 0;
	while (i)
	{
		arr[j++] = i->num;
		i = i->next;
	}
	sort_array(arr, size);
	i = head;
	while (i)
	{
		j = 0;
		while (j < size && i->num != arr[j])
			j++;
		i->index = j;
		i = i->next;
	}
	free(arr);
}

void	sort_array(int *arr, int size)
{
	int	a;
	int	b;
	int	temp;

	a = 0;
	while (a < size - 1)
	{
		b = a + 1;
		while (b < size)
		{
			if (arr[b] < arr[a])
			{
				temp = arr[b];
				arr[b] = arr[a];
				arr[a] = temp;
			}
			b++;
		}
		a++;
	}
}

void	medium(t_stacks *stacks)
{
	chunk_sort(stacks);
	return ;
}
