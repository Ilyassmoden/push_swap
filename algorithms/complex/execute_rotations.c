#include "../../push_swap.h"

/* Execute rotations when both costs have the same sign.
 * تنفيذ الدوران المشترك عندما تكون إشارتا التكلفة متشابهتين.
 */
void execute_same_sign(t_list *a, t_list *b,
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
            (c->cost_a < 0) ? "rra" : "ra", ops);
    else
        rotate_num(ft_abs(c->cost_b) - min, a, b,
            (c->cost_b < 0) ? "rrb" : "rb", ops);
}

/* Execute all rotations needed to move the cheapest node.
 * تنفيذ جميع الدورانات اللازمة لتحريك العنصر الأرخص.
 */
void execute_rotations(t_list *a, t_list *b,
        t_node *cheapest, size_t ops[11])
{
    if ((cheapest->cost_a < 0 && cheapest->cost_b < 0)
        || (cheapest->cost_a > 0 && cheapest->cost_b > 0))
        execute_same_sign(a, b, cheapest, ops);
    else
    {
        if (cheapest->cost_a < 0)
            rotate_num(ft_abs(cheapest->cost_a), a, b, "rra", ops);
        else if (cheapest->cost_a > 0)
            rotate_num(cheapest->cost_a, a, b, "ra", ops);
        if (cheapest->cost_b < 0)
            rotate_num(ft_abs(cheapest->cost_b), a, b, "rrb", ops);
        else if (cheapest->cost_b > 0)
            rotate_num(cheapest->cost_b, a, b, "rb", ops);
    }
}

/* Move the cheapest node from A to B.
 * نقل العنصر الأرخص من A إلى B.
 */
void    execute_moves(t_list *a, t_list *b,
        t_node *cheapest, size_t ops[11])
{
    if (!cheapest)
        return ;
    execute_rotations(a, b, cheapest, ops);
    push_pb(b, a, ops);
}

