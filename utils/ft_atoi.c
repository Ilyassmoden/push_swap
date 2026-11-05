/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:33:21 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/04 02:11:21 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *s, int *num)
{
	long long	n;
	int			sign;
	int			digits;

	while (*s && ft_isspace(*s))
		s++;
	sign = 1;
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -1;
	n = 0;
	digits = 0;
	while (*s && ft_isdigit(*s))
	{
		digits = 1;
		n = (n * 10) + (*s - '0');
		if (sign == 1 && n > 2147483647)
			return (0);
		else if (sign == -1 && n > 2147483648)
			return (0);
		s++;
	}
	if (!digits)
		return (0);
	*num = (int)(n * sign);
	return (!*s);
}
