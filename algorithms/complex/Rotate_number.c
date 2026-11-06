#include "../../push_swap.h"
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
