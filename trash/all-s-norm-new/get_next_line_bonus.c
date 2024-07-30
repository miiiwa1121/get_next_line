/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:30:00 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/30 18:51:32 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

char	*extract_line(char **save)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 0;
	if (!(*save)[i])
		return (NULL);
	while ((*save)[i] && ((*save)[i] != '\n' || i++))
		i++;
	line = (char *)malloc((i + 1 * sizeof(char)));
	if (!line)
		return (NULL);
	i = 0;
	while ((*save)[i] && (*save)[i] != '\n')
	{
		line[i] = (*save)[i];
		i++;
	}
	if ((*save)[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	tmp = *save;
	*save = ft_strjoin(*save + 1, "");
	free(tmp);
	return (line);
}

static char	*get_file(int fd, char *save)
{
	char	*buff;
	char	*tmp;
	int		bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 1;
	while ((!save || !ft_strchr(save, '\n')) && bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			if (save)
				free(save);
			return (NULL);
		}
		buff[bytes] = '\0';
		tmp = save;
		save = ft_strjoin(save, buff);
		free(tmp);
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[FOPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = get_file(fd, save[fd]);
	if (!save[fd])
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	line = extract_line(&save[fd]);
	if (line == NULL)
	{
		free(save[fd]);
		save[fd] = NULL;
	}
	return (line);
}
