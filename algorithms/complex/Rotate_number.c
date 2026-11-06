/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rotationB.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-elm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:19:43 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/06 17:19:44 by iait-elm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

/* Execute a rotation function several times.
 */
static void	rotate_while(int count, t_list *a, size_t ops[11],
		void (*f)(t_list *, size_t *))
{
	while (count > 0)
	{
		f(a, ops);
		count--;
	}
}

static void	rotate_while2(int count, t_stacks *st,
		void (*f)(t_list *, t_list *, size_t *))
{
	while (count > 0)
	{
		f(st->a, st->b, st->ops);
		count--;
	}
}

void	rotate_num(int count, char *s, t_stacks *st)
{
	if (ft_strcmp(s, "rra") == 0)
		rotate_while(count, st->a, st->ops, &rotate_rra);
	else if (ft_strcmp(s, "rrb") == 0)
		rotate_while(count, st->b, st->ops, &rotate_rrb);
	else if (ft_strcmp(s, "ra") == 0)
		rotate_while(count, st->a, st->ops, &rotate_ra);
	else if (ft_strcmp(s, "rb") == 0)
		rotate_while(count, st->b, st->ops, &rotate_rb);
	else if (ft_strcmp(s, "rr") == 0)
		rotate_while2(count, st, &rotate_rr);
	else if (ft_strcmp(s, "rrr") == 0)
		rotate_while2(count, st, &rotate_rrr);
}
