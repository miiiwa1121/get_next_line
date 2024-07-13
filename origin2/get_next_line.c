/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/11 15:56:18 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

#define MAX_FD 1024

/* 残りの文字列を保存する関数 */
static char	*save_str(char *save)
{
	size_t	i;
	size_t	j;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new_save = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!new_save)
	{
		free(save);
		return (NULL);
	}
	i++;
	j = 0;
	while (save[i])
	{
		new_save[j] = save[i];
		i++;
		j++;
	}
	new_save[j] = '\0';
	free(save);
	return (new_save);
}

/* 1行を抽出する関数 */
static char	*extract_line(char *save)
{
	size_t	i;
	char	*line;

	if (!save[0])
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

/* ファイルから読み込む関数 */
static char *get_line(int fd, char *save)
{
	static char buff[BUFFER_SIZE + 1];
	ssize_t bytes;
	char *tmp;

	while (1)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(save);
			return (NULL);
		}
		if (bytes == 0)
			break;
		buff[bytes] = '\0';
		tmp = ft_strjoin(save, buff);
		if (!tmp)
		{
			free(save);
			return (NULL);
		}
		free(save);
		save = tmp;
		if (ft_strchr(buff, '\n'))
			break;
	}
	return (save);
}

/* メイン関数 */
char	*get_next_line(int fd)
{
	static char	*save[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || BUFFER_SIZE > (SIZE_MAX - 1))
		return (NULL);
	save[fd] = get_line(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = extract_line(save[fd]);
	if (!line)
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	save[fd] = save_str(save[fd]);
	return (line);
}