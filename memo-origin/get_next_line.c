/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/13 23:14:05 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
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
		return (NULL);
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

// char	*get_line(int fd, char *save)
// {
// 	char	*buff;
// 	int		bytes;
// 	char	*tmp;

// 	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buff)
// 		return (NULL);
// 	bytes = 1;
// 	while (bytes > 0)
// 	{
// 		bytes = read(fd, buff, BUFFER_SIZE);
// 		if (bytes == -1)
// 		{
// 			free(buff);
// 			return (NULL);
// 		}
// 		buff[bytes] = '\0';
// 		tmp = ft_strjoin(save, buff);
// 		free(save);
// 		save = tmp;
// 		if (ft_strchr(buff, '\n'))
// 			break ;
// 	}
// 	free(buff);
// 	return (save);
// }

char	*get_line(int fd, char *save)
{
	static char	buff[BUFFER_SIZE + 1];
	int			bytes;
	char		*tmp;

	while (1)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes <= 0)
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
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (save);
}

char	*get_next_line(int fd)
{
	char	*line;

	static char *save; // static宣言は関数が終了しても変数に値が残っている
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = get_line(fd, save);
	/*fdからBUFFER_SIZE+1分のメモリを確保して、BUFFER_SIZ分ずつbuffへ読み込み、saveに追加格納する。
	saveへの格納後時点のbuffに改行を見つけたら、saveをリターンする。*/
	if (!save)
		return (NULL);
	line = extract_line(save);
	/* 改行が含まれているsaveの、改行もしくは終端までのバイト+2分のメモリを確保して、lineとする。
	引数saveが改行もしくは終端までの間、lineに先頭からコピーし、最後にNULLを入れて、リターンする。*/
	if (!line)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = save_str(save);
	/* 改行が含まれているsaveの、改行もしくは終端から終端までのバイト+1分のメモリを確保して、
	new_saveとする。引数saveが改行もしくは終端から終端までの間、new_saveに先頭からコピーし、
	最後にNULLを入れて、リターンする。 */
	return (line);
}

// #include <stdio.h>

// int main(void)
// {
//     int fd;
//     int i;
//     char *line;
//     const char *filename = "text1.txt";

//     i = 0;
//     fd = open(filename, O_RDWR);
//     if (fd < 0)
//     {
//         printf("openエラー\n");
//         return (1);
//     }
//     while ((line = get_next_line(fd)) != NULL && i < 7)
//     {
//         printf("line [%d]: %s\n", i, line);
//         free(line);
//         i++;
//     }
//     close(fd);
//     return (0);
// }
