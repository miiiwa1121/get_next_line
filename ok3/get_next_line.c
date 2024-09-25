/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:09:06 by jdecorte          #+#    #+#             */
/*   Updated: 2024/09/25 20:35:47 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*join_free(char *save, char *buff)
{
	char	*temp;

	temp = ft_strjoin(save, buff);//新しくメモリを確保して結合した値を格納し、アドレスを返す
	free(save);
	return (temp);
}

char	*next_line(char *save)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (save[i] && save[i] != '\n')//メモリの終端もしくは改行まで
		i++;
	if (!save[i])//改行が見つからない
	{
		free(save);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(save) - i + 1), sizeof(char));// 改行の次の文字から残りの部分を取得するためのメモリを確保 + 0埋め
	i++;
	j = 0;
	while (save[i])// 改行の次から終端までコピー
		line[j++] = save[i++];
	free(save);//必要なデータはlineに格納したので解放
	return (line);
}

char	*get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')//メモリの終端もしくは改行まで
		i++;
	line = ft_calloc(i + 2, sizeof(char));//(i + 2) * sizeof(char)分(+2 //改行＋'\n'分)メモリを確保して、0埋めして返す
	i = 0;
	while (save[i] && save[i] != '\n')//saveに蓄積されたデータから一行取り出す
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] && save[i] == '\n')//メモリの終端もしくは改行だったら
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *save)
{
	char	*buff;
	int		bytes;

	if (!save)
		save = ft_calloc(1, 1);//saveがメモリ確保してなかったら適当に確保 + 0埋め
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));//(BUFFER_SIZE+1) *sizeof(char)分メモリを確保して、0埋めして返す
	bytes = 1;
	while (bytes > 0)//読み込んだバイト数が正の間
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		// printf("@@@@@@@@@@%d@@@@@@@@@@\n",bytes);
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		save = join_free(save, buff);//結合後の新しいメモリのアドレスを返し、不要なメモリを解放
		if (ft_strchr(buff, '\n'))//文字を含まない改行を見つけたら
			break ;
	}
	// printf("*************%d**************\n",bytes);
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_file(fd, save);//バッファサイズ分ファイル読み込み
	if (!save)
		return (NULL);
	line = get_line(save);//行読み込み(１行＋改行を返す)
	save = next_line(save);//read_file(fd, save) - get_line(save) = next_line(save)
	return (line);
}
