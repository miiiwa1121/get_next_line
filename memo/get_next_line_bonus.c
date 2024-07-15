/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:30:00 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/15 14:49:07 by mtsubasa         ###   ########.fr       */
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
	while (save[i] && save[i] != '\n')//saveが終端では無い　&& saveが改行が無い
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new_save = malloc((ft_strlen(save) - i + 1) * sizeof(char));//saveのサイズ - saveの改行または終端までのサイズ + NULL分のメモリを確保
	if (!new_save)
	{
		free(save);
		return (NULL);
	}
	i++;//改行分進める
	j = 0;
	while (save[i])//saveの改行以降に値がある
		new_save[j++] = save[i++];//new_saveの先頭から順に、saveの改行以降を代入
	new_save[j] = '\0';//文字列の終端を知らせるために最後尾にNULLを格納
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
	while (save[i] && save[i] != '\n')//saveが終端では無い　&& saveが改行が無い
		i++;
	line = malloc((i + 2) * sizeof(char));//改行もしくは終端までのバイト+改行+NULL分のメモリを確保
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')//saveが終端では無い　&& saveが改行が無い
	{
		line[i] = save[i];//メモリ確保したlineにsaveの先頭から代入
		i++;
	}
	if (save[i] == '\n')//saveに改行がある(改行も含めて返さないといけない)
	{
		line[i] = save[i];//lineの末尾ににsaveの末尾(改行)を代入
		i++;
	}
	line[i] = '\0';//文字列の終端を知らせるために最後尾にNULLを格納
	return (line);
}

static char	*get_line(int fd, char *save)
{
	char	*buff;
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
		tmp = ft_strjoin(save, buff);//saveにbuffを結合し、tmpへ一時格納
		free(save);//save＋buffが格納されたメモリを解放
		save = tmp;//save＋buffが格納されたtmpをsaveへ格納
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
	/*fdからBUFFER_SIZE+NULL分のメモリを確保して、
	saveが何も読み込んでないまたは、saveに改行が見るからないそして、read読み込みに失敗していない間、
	BUFFER_SIZ分ずつbuffへ読み込み、saveに追加格納する。
	ループ条件で、saveに改行を見つけたら、ループを抜けてsaveをリターンする。*/
	if (!save[fd])//get_lineで上手く読み込めなかったらNULLがsaveに格納されるので、その場合弾く
		return (NULL);
	line = extract_line(save[fd]);//get_line(fd, save[fd])で得たsave[fd]から改行までを抜粋(改行も含めて抜粋)
	/* 改行が含まれているsaveの、改行もしくは終端までのバイト+改行+NULL分のメモリを確保して、lineとする。
	引数saveが改行もしくは終端までの間、lineに先頭からコピーし、最後にNULLを入れて、リターンする。*/
	save[fd] = save_str(save[fd]);//get_line(fd, save[fd])で得たsave[fd]からextract_line(save[fd])を引いたあまりを保存
	/* 改行が含まれているsaveの、改行もしくは終端から終端までのバイト+NULL分のメモリを確保して、
	new_saveとする。引数saveが改行もしくは終端から終端までの間、new_saveに先頭からコピーし、
	最後にNULLを入れて、リターンする。 */
	return (line);
}
/////////////