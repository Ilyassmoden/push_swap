#include "../push_swap.h"

/* Return the absolute value of a number.
 * إرجاع القيمة المطلقة للعدد.
 */
 int ft_abs(int n)
{
    if (n < 0)
        return (n * -1);
    return (n);
}

/* Return the greater of two numbers.
 * إرجاع العدد الأكبر.
 */
int ft_max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

/* Return the smaller of two numbers.
 * إرجاع العدد الأصغر.
 */
int ft_min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}

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

/* Execute a rotation function several times.
 * تنفيذ عملية دوران عدة مرات.
 */
static void rotate_while(int count, t_list *a, size_t ops[11],
        void (*f)(t_list *, size_t *))
{
    while (count > 0)
    {
        f(a, ops);
        count--;
    }
}

static void rotate_while2(int count, t_list *a, t_list *b,
        size_t ops[11],
        void (*f)(t_list *, t_list *, size_t *))
{
    while (count > 0)
    {
        f(a, b, ops);
        count--;
    }
}

void    rotate_num(int count, t_list *a, t_list *b,
        char *s, size_t ops[11])
{
    if (ft_strcmp(s, "rra") == 0)
        rotate_while(count, a, ops, &rotate_rra);
    else if (ft_strcmp(s, "rrb") == 0)
        rotate_while(count, b, ops, &rotate_rrb);
    else if (ft_strcmp(s, "ra") == 0)
        rotate_while(count, a, ops, &rotate_ra);
    else if (ft_strcmp(s, "rb") == 0)
        rotate_while(count, b, ops, &rotate_rb);
    else if (ft_strcmp(s, "rr") == 0)
        rotate_while2(count, a, b, ops, &rotate_rr);
    else if (ft_strcmp(s, "rrr") == 0)
        rotate_while2(count, a, b, ops, &rotate_rrr);
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

/* Execute rotations when both costs have the same sign.
 * تنفيذ الدوران المشترك عندما تكون إشارتا التكلفة متشابهتين.
 */
static void execute_same_sign(t_list *a, t_list *b,
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
static void execute_rotations(t_list *a, t_list *b,
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

/* Find the correct target in A and move the cheapest node from B.
 * إيجاد المكان المناسب في A ثم نقل العنصر الأرخص من B.
 */
static t_node *find_next_bigger(t_list *a, int num)
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
static t_node *find_min_node(t_list *a)
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
static void find_target_b_to_a(t_list *b, t_list *a)
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
/* Move all elements from B back to A in the correct order.
 * إعادة جميع عناصر B إلى A بالترتيب الصحيح.
 */
void    sort_b_to_a(t_list *a, t_list *b, size_t ops[11])
{
    while (get_stack_size(b) > 0)
        find_target_b(a, b, ops);
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