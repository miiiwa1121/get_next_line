/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/08/01 23:27:16 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

static char	*supp_extract_line(char *save, char *line)
{
	int	i;

	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*extract_line(char *save)
{
	int		i;
	char	*line;
	int		flag;

	i = 0;
	flag = 0;
	if (!save[i])
		return (NULL);
	if (ft_strchr(save, '\n'))
		flag = 1;
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc((i + 1 + flag) * sizeof(char));
	if (!line)
	{
		free(save);
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
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = get_line(fd, save);
	if (!save)
		return (NULL);
	line = extract_line(save);
	if (save)
		save = save_str(save);
	return (line);
}
