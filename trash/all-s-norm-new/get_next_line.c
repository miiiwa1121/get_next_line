/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/22 16:20:33 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

static char	*extract_line(char **save)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 0;
	if (!(*save))
		return (NULL);
	while ((*save)[i] && ((*save)[i] == '\n' || i++))
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
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

static char	*get_file(int fd, char **save)
{
	char	*buff;
	int		bytes;
	char	*tmp;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 1;
	while ((!save || !ft_strchr(*save, '\n')) && bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		tmp = *save;
		*save = ft_strjoin(*save, buff);
		free(tmp);
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save != NULL)
		save = ft_strjoin("", "");
	save = get_file(fd, &save);
	if (!save)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	line = extract_line(&save);
	if (!save)
	{
		free(save);
		save = NULL;
	}
	return (line);
}
