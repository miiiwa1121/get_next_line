/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:30:00 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/30 18:03:48 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static char	*supp_extract_line(char **save, char *line)
{
	int	i;

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
		if (*save)
			free(*save);
		*save = NULL;
		return (NULL);
	}
	line = supp_extract_line(save, line);
	return (line);
}

static char	*supp_get_line(int fd, char *save, char *buff)
{
	int		bytes;
	char	*tmp;

	while (!save || !ft_strchr(save, '\n'))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(save);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		tmp = ft_strjoin(save, buff);
		if (!tmp)
		{
			free(save);
			return (NULL);
		}
		free(save);
		save = tmp;
	}
	return (save);
}

static char	*get_line(int fd, char *save)
{
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
	{
		if (save)
			free(save);
		return (NULL);
	}
	save = supp_get_line(fd, save, buff);
	free(buff);
	if (!save)
		return (NULL);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[FOPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	save[fd] = get_line(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = extract_line(&save[fd]);
	if (save[fd])
		save[fd] = save_str(save[fd]);
	return (line);
}
