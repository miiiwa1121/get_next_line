/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/14 15:20:53 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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
	char	*buff;//一時読み込み
	int		bytes;//読み込んだバイト数 or -1(失敗)
	char	*tmp;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));//BUFFER_SIZE+NULL分のメモリを確保
	if (!buff)
		return (NULL);
	bytes = 1;
	while ((!save || !ft_strchr(save, '\n')) && bytes > 0)//saveが未読み込み || saveに改行が改行が無い && readに失敗
	{
		bytes = read(fd, buff, BUFFER_SIZE);//fdからBUFF_SIZE分をbuffへ格納して、bytesへ読み込んだバイト数 or -1(失敗)を返す
		if (bytes == -1)//readの格納に失敗
		{
			free(buff);//buffを解放
			free(save);//ft_strjoinで確保したメモリを解放
			return (NULL);
		}
		buff[bytes] = '\0';//ft_strjoinで文字列の終端を知らせるために最後尾にNULLを格納
		tmp = ft_strjoin(save, buff);//saveにbuffを格納し、tmpへ一時格納
		free(save);//save＋buffが格納されたメモリを解放
		save = tmp;//save＋buffが格納されたtmpをsaveへ格納
	}
	free(buff);//buffを解放
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;//static宣言は関数が終了しても変数に値が残っている//staticはNULLで初期化される

	if (fd < 0 || BUFFER_SIZE <= 0)//無効なファイルディスクリプタ || BUFFER_SIZEが0以下
		return (NULL);
	save = get_line(fd, save);//fdから一行ぴったりもしくは、改行を含む文字列がsaveへ格納される 
	/*fdからBUFFER_SIZE+1分のメモリを確保して、
	saveが何も読み込んでないまたは、saveに改行が見るからないそして、read読み込みに失敗していない間、
	BUFFER_SIZ分ずつbuffへ読み込み、saveに追加格納する。
	ループ条件で、saveに改行を見つけたら、saveをリターンする。*/
	if (!save)//get_lineで上手く読み込めなかったらNULLがsaveに格納されるので、その場合弾く
		return (NULL);
	line = extract_line(save);
	/* 改行が含まれているsaveの、改行もしくは終端までのバイト+2分のメモリを確保して、lineとする。
	引数saveが改行もしくは終端までの間、lineに先頭からコピーし、最後にNULLを入れて、リターンする。*/
	save = save_str(save);
	/* 改行が含まれているsaveの、改行もしくは終端から終端までのバイト+1分のメモリを確保して、
	new_saveとする。引数saveが改行もしくは終端から終端までの間、new_saveに先頭からコピーし、
	最後にNULLを入れて、リターンする。 */
	return (line);
}
