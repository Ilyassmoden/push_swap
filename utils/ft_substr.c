/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 00:39:43 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/03 01:22:26 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	alloc_len;
	char	*str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (s_len - start < len)
		alloc_len = s_len - start;
	else
		alloc_len = len;
	str = malloc(sizeof(char) * (alloc_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s[start], alloc_len + 1);
	return (str);
}
