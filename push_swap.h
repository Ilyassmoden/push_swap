/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 22:43:02 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/03 23:17:55 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

# define SIMPLE_FLAG "--simple"
# define MEDIUM_FLAG "--medium"
# define COMPLEX_FLAG "--complex"
# define ADAPTIVE_FLAG "--adaptive"
# define BENCH_FLAG "--bench"

# define SIMPLE_IDX 0
# define MEDIUM_IDX 1
# define COMPLEX_IDX 2
# define ADAPTIVE_IDX 3
# define BENCH_IDX 4

# define SA 0
# define SB 1
# define SS 2
# define PA 3
# define PB 4
# define RA 5
# define RB 6
# define RR 7
# define RRA 8
# define RRB 9
# define RRR 10

typedef struct s_node
{
    int             num;
    int             index;
    int             target_index;
    int             cost_a;
    int             cost_b;
    int             total_cost;
    struct s_node   *next;
	struct s_node 	*prev;
}   t_node;

typedef struct s_list
{
	int size;
	t_node	*head;
	t_node	*tail;
}	t_list;

/* Algorithms */
void	simple(t_list *a, t_list *b, size_t ops[11]);
void	medium(t_list *a, t_list *b, size_t ops[11]);
void	complex(t_list *a, t_list *b, size_t ops[11]);

//fonction heap for algorithms
int	get_stack_size(t_list *a);
void rotate_num(int count,t_list *a,t_list *b,char *s,size_t ops[11]);

/* Operations */
void	swap_sa(t_node *a, t_node *b, size_t ops[RRR + 1]);
void	swap_sb(t_node *a, t_node *b, size_t ops[RRR + 1]);
void	swap_ss(t_list *stack_a, t_list *stack_b, size_t ops[RRR + 1]);

void	push_pa(t_list *stack_b, t_list *stack_a, size_t ops[RRR + 1]);
void	push_pb(t_list *stack_b, t_list *stack_a, size_t ops[RRR + 1]);

void	rotate_ra(t_list *stack_a, size_t ops[RRR + 1]);
void	rotate_rb(t_list *stack_b, size_t ops[RRR + 1]);
void	rotate_rr(t_list *stack_a, t_list *stack_b, size_t ops[RRR + 1]);

void	rotate_rra(t_list *stack_a, size_t ops[RRR + 1]);
void	rotate_rrb(t_list *stack_b, size_t ops[RRR + 1]);
void	rotate_rrr(t_list *stack_a, t_list *stack_b, size_t ops[RRR + 1]);

/* Utils */
int		ft_atoi(const char *s, int *n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);
void	ft_bzero(void *s, size_t n);
void	ft_lstadd_back(t_list *list, t_node *node);
void	ft_lstclear(t_list *list);
void	ft_putnbr_fd(int fd, int n);
void	ft_putstr_fd(int fd, const char *s);
t_node	*ft_lstnew(int num);

/*Parsing*/
int		parse_input(int ac, char **av, t_list *a,
			int flags[BENCH_IDX + 1]);

/* Algorithm selection */
void	print_algorithm(t_list *a, t_list *b,
			int flags[BENCH_IDX + 1]);

/* Benchmark */
void	print_bench(int flags[BENCH_IDX + 1], float disorder,
			size_t ops[RRR + 1]);

#endif
