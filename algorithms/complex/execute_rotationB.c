#include "../../push_swap.h"

/* Move the cheapest node from B back to A.
 * إعادة العنصر الأرخص من B إلى A.
 */
static void execute_same_sign_b(t_list *a, t_list *b,
        t_node *c, size_t ops[11])
{
    int min;

    min = ft_min(ft_abs(c->cost_a), ft_abs(c->cost_b));
    if (c->cost_a < 0)
        rotate_num(min, a, b, "rrr", ops);
    else
        rotate_num(min, a, b, "rr", ops);
    if (ft_abs(c->cost_a) > ft_abs(c->cost_b))
        rotate_num(ft_abs(c->cost_a) - min, a, b,
            (c->cost_a < 0) ? "rrb" : "rb", ops);
    else
        rotate_num(ft_abs(c->cost_b) - min, a, b,
            (c->cost_b < 0) ? "rra" : "ra", ops);
}
static void execute_rotations_b(t_list *a, t_list *b,
        t_node *c, size_t ops[11])
{
    if ((c->cost_a < 0 && c->cost_b < 0)
        || (c->cost_a > 0 && c->cost_b > 0))
        execute_same_sign_b(a, b, c, ops);
    else
    {
        if (c->cost_a < 0)
            rotate_num(ft_abs(c->cost_a), a, b, "rrb", ops);
        else if (c->cost_a > 0)
            rotate_num(c->cost_a, a, b, "rb", ops);
        if (c->cost_b < 0)
            rotate_num(ft_abs(c->cost_b), a, b, "rra", ops);
        else if (c->cost_b > 0)
            rotate_num(c->cost_b, a, b, "ra", ops);
    }
}
void    execute_moves_b(t_list *a, t_list *b,
        t_node *cheapest, size_t ops[11])
{
    if (!cheapest)
        return ;
    execute_rotations_b(a, b, cheapest, ops);
    push_pa(b, a, ops);
}
