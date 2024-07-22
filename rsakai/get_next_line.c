/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resakai <resakai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:29:13 by resakai           #+#    #+#             */
/*   Updated: 2024/07/18 09:27:10 by resakai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

static char	*ft_get_line(char **stash)
{
	char	*line;
	char	*temp;
	int		index;

	index = 0;
	if (*stash == NULL)
		return (NULL);
	while ((*stash)[index] != '\0' && ((*stash)[index] == '\n' || index++))
		index++;
	line = (char *)malloc(sizeof(char) * (index + 1));
	if (line == NULL)
		return (NULL);
	index = 0;
	while ((*stash)[index] != '\0' && (*stash)[index] != '\n')
	{
		line[index] = (*stash)[index];
		index++;
	}
	if ((*stash)[index] == '\n')
		line[index++] = '\n';
	line[index] = '\0';
	temp = *stash;
	*stash = ft_strjoin(*stash + 1, "");
	free(temp);
	return (line);
}

static char	*ft_read_file(int fd, char **stash)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = *stash;
		*stash = ft_strjoin(*stash, buffer);
		free(temp);
	}
	free(buffer);
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash != NULL)
		stash = ft_strjoin("", "");
	if (ft_read_file(fd, &stash) == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_get_line(&stash);
	if (line == NULL)
	{
		free(stash);
		stash = NULL;
	}
	return (line);
}
