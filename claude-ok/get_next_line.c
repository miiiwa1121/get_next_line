/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/14 00:08:42 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

static char	*read_line(int fd, char *buffer, char **backup)
{
	int		read_bytes;
	char	*temp;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(*backup);
			*backup = NULL;
			return (NULL);
		}
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		if (!*backup)
			*backup = ft_strdup("");
		temp = *backup;
		*backup = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*backup);
}

static char	*extract_line(char **line)
{
	size_t	i;
	char	*backup;

	i = 0;
	while ((*line)[i] != '\n' && (*line)[i] != '\0')
		i++;
	if ((*line)[i] == '\0')
		return (NULL);
	backup = ft_substr(*line, i + 1, ft_strlen(*line) - i);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	(*line)[i + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_line(fd, buffer, &backup);
	free(buffer);
	if (!line)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = extract_line(&line);
	return (line);
}
