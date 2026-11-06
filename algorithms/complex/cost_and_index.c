
#include "../../push_swap.h"

/* Assign current positions to both stacks.
 * حساب المواقع الحالية للعناصر في A و B.
 */
void    assign_index(t_list *a, t_list *b)
{
    t_node  *i;
    int     p;

    i = a->head;
    p = 0;
    while (i)
    {
        i->index = p++;
        i = i->next;
    }
    if (b)
    {
        i = b->head;
        p = 0;
        while (i)
        {
            i->index = p++;
            i = i->next;
        }
    }
}
/* Calculate the movement costs for every node in A.
 * حساب تكلفة تحريك كل عنصر من A والـ target الخاص به في B.
 */
void    calculate_cost(t_list *a, t_list *b)
{
    t_node  *i;
    int     size_a;
    int     size_b;

    i = a->head;
    size_a = get_stack_size(a);
    size_b = get_stack_size(b);
    while (i)
    {
        if (size_a / 2 < i->index)
            i->cost_a = (size_a - i->index) * -1;
        else
            i->cost_a = i->index;
        if (size_b / 2 < i->target_index)
            i->cost_b = (size_b - i->target_index) * -1;
        else
            i->cost_b = i->target_index;
        if ((i->cost_a < 0 && i->cost_b < 0)
            || (i->cost_a > 0 && i->cost_b > 0))
            i->total_cost = ft_max(ft_abs(i->cost_a),
                    ft_abs(i->cost_b));
        else
            i->total_cost = ft_abs(i->cost_a) + ft_abs(i->cost_b);
        i = i->next;
    }
}
/* Find the node with the lowest total movement cost.
 * إيجاد العنصر الذي يملك أقل تكلفة للحركة.
 */
t_node  *find_cheapest(t_list *a)
{
    t_node  *min;
    t_node  *i;

    if (!a || !a->head)
        return (NULL);
    min = a->head;
    i = a->head->next;
    while (i)
    {
        if (i->total_cost < min->total_cost)
            min = i;
        i = i->next;
    }
    return (min);
}
