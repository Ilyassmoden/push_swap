/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 22:43:02 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/07 09:21:36 by yalahian         ###   ########.fr       */
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

# define SA "sa"
# define SB "sb"
# define SS "ss"
# define PA "pa"
# define PB "pb"
# define RA "ra"
# define RB "rb"
# define RR "rr"
# define RRA "rra"
# define RRB "rrb"
# define RRR "rrr"

# define SA_IDX 0
# define SB_IDX 1
# define SS_IDX 2
# define PA_IDX 3
# define PB_IDX 4
# define RA_IDX 5
# define RB_IDX 6
# define RR_IDX 7
# define RRA_IDX 8
# define RRB_IDX 9
# define RRR_IDX 10

# define BUFFER_SIZE 1024

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	int				cost_a;
	int				cost_b;
	int				index;
	int				num;
	int				target_index;
	int				total_cost;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	size_t	size;
}	t_list;

typedef struct s_op
{
	char	*label;
	size_t	count;
}	t_op;

typedef struct s_stacks
{
	t_list	a;
	t_list	b;
	t_op	ops[RRR_IDX + 1];
}	t_stacks;

// algorithms
void	simple(t_stacks *stacks);
void	medium(t_stacks *stacks);
//--->
void	chunk_sort(t_stacks *stacks);//algoritmes
void	sort_array(int *arr, int size);//sort_normal_array
void	index_stack(t_node *head, int size);//indexing
int		get_chunk_size(int size);//chunkin
int		get_stack_size(t_list *a);
//--->
void	complex(t_stacks *stacks);
//---------->
void	sort_three(t_stacks *stacks);
void	sort_b_to_a(t_stacks *stacks);
void	find_target_b(t_stacks *stacks);
void	sort_a_to_b(t_stacks *stacks);
void	assign_index(t_stacks *stacks);
void	find_target(t_stacks *stacks);
void	find_target_b_to_a(t_stacks *stacks);
void	calculate_cost(t_stacks *stacks);
void	calculate_cost_b_to_a(t_stacks *stacks);
t_node	*find_cheapest(t_stacks *stacks);
t_node	*find_cheapest_b(t_stacks *stacks);
void	execute_moves(t_stacks *stacks, t_node *cheapest);
void	execute_moves_b(t_stacks *stacks, t_node *cheapest);
void	final_rotate(t_stacks *stacks);
void	rotate_num(int count, char *s, t_stacks *stacks);
void	calc_node_cost(t_node *node, int size_a, int size_b);
int		ft_abs(int n);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
//---------->

// operations
void	swap(t_stacks *stacks, int op_idx, int silent);
void	push(t_stacks *stacks, int op_idx, int silent);
void	rotate(t_stacks *stacks, int op_idx, int silent);
void	rrotate(t_stacks *stacks, int op_idx, int silent);

// utils
int		ft_atoi(const char *s, int *n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strndup(char *s, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	**ft_split(const char *s, char c);
void	ft_bzero(void *s, size_t n);
void	ft_lstadd_back(t_list *list, t_node *node);
void	ft_lstadd_front(t_list *list, t_node *node);
void	ft_lstclear(t_list *list);
void	ft_lstiteri(t_list *list, void (*f)(t_node *node));
void	ft_putnbr_fd(int fd, int n);
void	ft_putstr_fd(int fd, const char *s);
t_node	*ft_lstnew(int num);

// mandatory
int		parse_input(int ac, char **av, t_list *a, int *flags);
void	print_bench(t_stacks stacks, int *flags, float disorder);

// bonus
int		parse_input_bonus(int ac, char **av, t_list *a);

#endif
