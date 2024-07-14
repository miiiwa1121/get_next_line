/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:30:00 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/14 15:26:34 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <limits.h>

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

char	*extract_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
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
		line[i] = save[i];
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
		return (NULL);
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
	static char	*save[OPEN_MAX];//静的変数saveをファイルディスクリプタごとに管理するため、ファイルディスクリプタの最大数の配列サイズを確保

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)//無効なファイルディスクリプタ(下限) || BUFFER_SIZEが0以下 || 無効なファイルディスクリプタ(上限)
	//OPEN_MAX>システム上で同時に開くことができるファイルディスクリプタの最大数を定義する定数
		return (NULL);
	save[fd] = get_line(fd, save[fd]);//fdからsave[fd]へ文字列を格納
	if (!save[fd])
		return (NULL);
	line = extract_line(save[fd]);//get_line(fd, save[fd])で得たsave[fd]から改行までを抜粋
	save[fd] = save_str(save[fd]);//get_line(fd, save[fd])で得たsave[fd]からextract_line(save[fd])を引いたあまりを保存
	return (line);
}
