/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-elm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 15:18:36 by iait-elm          #+#    #+#             */
/*   Updated: 2026/11/06 15:18:37 by iait-elm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_abs(int n)
{
    if (n < 0)
        return (n * -1);
    return (n);
}

int ft_max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

int ft_min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}
