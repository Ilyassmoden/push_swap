/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalahian <yalahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 17:29:32 by yalahian          #+#    #+#             */
/*   Updated: 2026/11/07 07:36:00 by yalahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static char	*ft_strchr(char *s, char c)
{
	while (s && *s && *s != c)
		s++;
	if (s && *s == c)
		return (s);
	return (NULL);
}

static char	*ft_strljoin(char *s1, char *s2, size_t s2_len)
{
	size_t	i;
	size_t	s1_len;
	char	*str;

	s1_len = ft_strlen(s1);
	if (!s1_len)
		return (ft_strndup(s2, s2_len));
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		str[s1_len + i] = s2[i];
		i++;
	}
	str[s1_len + s2_len] = '\0';
	return (str);
}

static int	read_file(int fd, char *buffer, char **stash)
{
	ssize_t	bytes;
	char	*temp;

	while (!ft_strchr(*stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (0);
		if (bytes == 0)
			return (1);
		buffer[bytes] = '\0';
		temp = ft_strljoin(*stash, buffer, bytes);
		if (!temp)
			return (0);
		free(*stash);
		*stash = temp;
	}
	return (1);
}

static int	read_stash(char **stash, char **line)
{
	char	*endl;
	char	*temp;

	if (!*stash || **stash == '\0')
		return (0);
	endl = ft_strchr(*stash, '\n');
	if (!endl)
	{
		*line = ft_strndup(*stash, ft_strlen(*stash));
		if (!*line)
			return (0);
		free(*stash);
		*stash = NULL;
		return (1);
	}
	*line = ft_strndup(*stash, endl - *stash);
	if (!*line)
		return (0);
	temp = ft_strndup(endl + 1, ft_strlen(endl + 1));
	if (!temp)
		return (0);
	free(*stash);
	*stash = temp;
	return (1);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = NULL;
	if (!read_file(fd, buffer, &stash) || !read_stash(&stash, &line))
	{
		free(stash);
		stash = NULL;
		free(line);
		line = NULL;
	}
	free(buffer);
	return (line);
}
