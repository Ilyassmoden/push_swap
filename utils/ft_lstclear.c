/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 00:24:11 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/07 07:51:24 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_lstclear(t_list *a)
{
	t_node	*temp;

	if (!a)
		return ;
	while (a->head)
	{
		temp = a->head->next;
		free(a->head);
		a->head = temp;
	}
	a->tail = NULL;
	a->size = 0;
}
