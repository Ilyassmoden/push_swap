#include "../../push_swap.h"

/* Run the complete Turk Sort algorithm.
 * تشغيل خوارزمية Turk Sort بجميع مراحلها.
 */
void    complex(t_list *a, t_list *b, size_t ops[11])
{
    if (get_stack_size(a) == 2)
    {
        if (a->head->num > a->head->next->num)
            swap_sa(a->head, NULL, ops);
    }
    else if (get_stack_size(a) == 3)
        sort_three(a, ops);
    else if (get_stack_size(a) > 3)
    {
        push_pb(b, a, ops);
        push_pb(b, a, ops);
        sort_a_to_b(a, b, ops);
        if (get_stack_size(a) == 2)
        {
            if (a->head->num > a->head->next->num)
                swap_sa(a->head, NULL, ops);
        }
        else
            sort_three(a, ops);
        sort_b_to_a(a, b, ops);
        final_rotate(a, ops);
    }
}