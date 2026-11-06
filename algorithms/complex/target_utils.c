#include "../../push_swap.h"

/* Find the target node in stack B for every node in A.
 * إيجاد أكبر عنصر أصغر من كل عنصر في A داخل B.
 */
void    find_target(t_list *a, t_list *b)
{
    t_node  *i;
    t_node  *j;
    t_node  *target;
    t_node  *max;

    i = a->head;
    while (i && b->head)
    {
        j = b->head;
        target = NULL;
        while (j)
        {
            if (i->num > j->num
                && (!target || j->num > target->num))
                target = j;
            j = j->next;
        }
        if (!target)
        {
            j = b->head;
            max = j;
            while (j)
            {
                if (j->num > max->num)
                    max = j;
                j = j->next;
            }
            target = max;
        }
        i->target_index = target->index;
        i = i->next;
    }
}
/* Find the correct target in A and move the cheapest node from B.
 * إيجاد المكان المناسب في A ثم نقل العنصر الأرخص من B.
 */
t_node *find_next_bigger(t_list *a, int num)
{
    t_node  *j;
    t_node  *target;

    j = a->head;
    target = NULL;
    while (j)
    {
        if (j->num > num && (!target || j->num < target->num))
            target = j;
        j = j->next;
    }
    return (target);
}
t_node *find_min_node(t_list *a)
{
    t_node  *j;
    t_node  *min;

    j = a->head;
    min = j;
    while (j)
    {
        if (j->num < min->num)
            min = j;
        j = j->next;
    }
    return (min);
}
void find_target_b_to_a(t_list *b, t_list *a)
{
    t_node  *i;
    t_node  *target;

    if (!a || !a->head || !b)
        return ;
    i = b->head;
    while (i)
    {
        target = find_next_bigger(a, i->num);
        if (!target)
            target = find_min_node(a);
        i->target_index = target->index;
        i = i->next;
    }
}

/* Put the smallest element at the top of stack A.
 * وضع أصغر عنصر في أعلى Stack A.
 */
void    final_rotate(t_list *a, size_t ops[11])
{
    t_node  *current;
    int     min;
    int     index;
    int     size;

    if (!a || !a->head)
        return ;
    assign_index(a, NULL);
    current = a->head;
    min = current->num;
    index = current->index;
    size = get_stack_size(a);
    while (current)
    {
        if (current->num < min)
        {
            min = current->num;
            index = current->index;
        }
        current = current->next;
    }
    if (index <= size / 2)
        rotate_num(index, a, NULL, "ra", ops);
    else
        rotate_num(size - index, a, NULL, "rra", ops);
}
