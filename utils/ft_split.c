/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:32:02 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/02 23:47:46 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static size_t	count_strs(const char *s, char c)
{
	size_t	count;
	int		is_valid;

	count = 0;
	is_valid = 1;
	while (*s)
	{
		if (*s == c)
			is_valid = 1;
		else if (is_valid)
		{
			is_valid = 0;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*get_substr(const char *s, char c, size_t *i)
{
	size_t	j;
	size_t	str_len;

	j = *i;
	str_len = 0;
	while (s[j] && s[j] == c)
		j++;
	while (s[j + str_len] && s[j + str_len] != c)
		str_len++;
	*i = j + str_len;
	return (ft_substr(s, (unsigned int)j, str_len));
}

static void	*free_strs(char **strs, size_t size)
{
	while (size > 0)
	{
		size--;
		free(strs[size]);
	}
	free(strs);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	strs_count;
	char	**strs;

	if (!s)
		return (NULL);
	strs_count = count_strs(s, c);
	strs = malloc(sizeof(char *) * (strs_count + 1));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (i < strs_count)
	{
		strs[i] = get_substr(s, c, &j);
		if (!strs[i])
			return (free_strs(strs, i));
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
