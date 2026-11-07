/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 22:34:21 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/07 03:44:42 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_lstadd_front(t_list *list, t_node *node)
{
	if (!list || !node)
		return ;
	node->prev = NULL;
	if (list->size)
	{
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}
	else
	{
		node->next = NULL;
		list->head = node;
		list->tail = node;
	}
	list->size++;
}
