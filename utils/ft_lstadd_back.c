/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 23:54:31 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/03 00:13:54 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_lstadd_back(t_list *list, t_node *node)
{
	if (!list || !node)
		return ;
	node->next = NULL;
	if (list->size)
	{
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
	else
	{
		node->prev = NULL;
		list->head = node;
		list->tail = node;
	}
	list->size++;
}
