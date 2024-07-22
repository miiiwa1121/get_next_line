/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:30:00 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/22 16:39:11 by mtsubasa         ###   ########.fr       */
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
	int		flag;

	i = 0;
	flag = 0;
	if (!(*save)[i])
		return (NULL);
	if (ft_strchr(*save, '\n'))
		flag = 1;
	while ((*save)[i] && (*save)[i] != '\n')
		i++;
	line = malloc((i + 1 + flag) * sizeof(char));
	if (!line)
	{
		free(*save);
		*save = NULL;
		return (NULL);
	}
	i = 0;
	while ((*save)[i] && (*save)[i] != '\n')
	{
		line[i] = (*save)[i];
		i++;
	}
	if ((*save)[i] == '\n')
	{
		line[i] = (*save)[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*free_and_return(char *ptr1, char *ptr2)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	return (NULL);
}

static char	*read_and_save(int fd, char *save)
{
	char	*buff;
	int		bytes;
	char	*tmp;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (free_and_return(save, NULL));
	bytes = 1;
	while ((!save || !ft_strchr(save, '\n')) && bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (free_and_return(buff, save));
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		tmp = ft_strjoin(save, buff);
		free(save);
		save = tmp;
	}
	free(buff);
	return (save);
}

static char	*process_line(char **save)
{
	char	*line;

	line = extract_line(save);
	if (*save)
		*save = save_str(*save);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = read_and_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	return (process_line(&save[fd]));
}
