/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/20 12:44:00 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

char	*save_str(char *save)
{
	int		i;
	int		j;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new_save = malloc((ft_strlen(save) - i + 1) * sizeof(char));
	if (!new_save)
	{
		free(save);
		return (NULL);
	}
	i++;
	j = 0;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	free(save);
	return (new_save);
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

static char	*get_line(int fd, char *save)
{
	char	*buff;
	int		bytes;
	char	*tmp;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
	{
		if (save)
			free(save);
		return (NULL);
	}
	bytes = 1;
	while ((!save || !ft_strchr(save, '\n')) && bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			free(save);
			return (NULL);
		}
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

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = get_line(fd, save);
	if (!save)
		return (NULL);
	line = extract_line(&save);
	if (save)
		save = save_str(save);
	return (line);
}