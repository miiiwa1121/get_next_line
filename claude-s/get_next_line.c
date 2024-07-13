/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/14 00:26:07 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	while (s && *s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
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
		if (!*backup)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*backup);
}

static char	*extract_line(char **line)
{
	char	*backup;
	char	*nl_ptr;
	size_t	len;

	nl_ptr = ft_strchr(*line, '\n');
	if (!nl_ptr)
	{
		backup = NULL;
		return (backup);
	}
	len = nl_ptr - *line + 1;
	backup = ft_substr(*line, len, ft_strlen(*line) - len);
	if (!backup)
		return (NULL);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	(*line)[len] = '\0';
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
	if (!backup && !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
