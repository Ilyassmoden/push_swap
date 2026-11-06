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
/* Sort exactly three elements in ascending order.
 * ترتيب ثلاثة عناصر تصاعدياً.
 */
void    sort_three(t_list *a, size_t ops[11])
{
    int first;
    int second;
    int third;

    if (!a || !a->head || !a->head->next
        || !a->head->next->next)
        return ;
    first = a->head->num;
    second = a->head->next->num;
    third = a->head->next->next->num;
    if (first > second && second > third)
    {
        swap_sa(a->head, NULL, ops);
        rotate_rra(a, ops);
    }
    else if (first > second && first > third)
        rotate_ra(a, ops);
    else if (second > third && first < third)
    {
        swap_sa(a->head, NULL, ops);
        rotate_ra(a, ops);
    }
    else if (second > third)
        rotate_rra(a, ops);
    else if (first > second)
        swap_sa(a->head, NULL, ops);
}
/* Move all elements from B back to A in the correct order.
 * إعادة جميع عناصر B إلى A بالترتيب الصحيح.
 */
void    sort_b_to_a(t_list *a, t_list *b, size_t ops[11])
{
    while (get_stack_size(b) > 0)
        find_target_b(a, b, ops);
}

void    find_target_b(t_list *a, t_list *b, size_t ops[11])
{
    t_node  *cheapest;

    if (!a || !a->head || !b || !b->head)
        return ;
    assign_index(a, b);
    find_target_b_to_a(b, a);
    calculate_cost(b, a);
    cheapest = find_cheapest(b);
    execute_moves_b(a, b, cheapest, ops);
}

/* Keep three elements in A by moving the cheapest nodes to B.
 * نقل العناصر من A إلى B حتى تبقى ثلاثة عناصر في A.
 */
void    sort_a_to_b(t_list *a, t_list *b, size_t ops[11])
{
    t_node  *cheapest;

    while (get_stack_size(a) > 3)
    {
        assign_index(a, b);
        find_target(a, b);
        calculate_cost(a, b);
        cheapest = find_cheapest(a);
        execute_moves(a, b, cheapest, ops);
    }
}
