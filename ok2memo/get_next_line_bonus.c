/* 42 School のヘッダー */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:23:39 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/09/09 00:58:29 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 必要なヘッダーファイルのインクルード */
#include "get_next_line.h"  // プロジェクト固有のヘッダーファイル
#include <limits.h>         // FOPEN_MAX の定義のため
#include <stdio.h>          // 標準入出力関数のため
#include <stdlib.h>         // メモリ割り当て関数のため

/* save_str: 読み込んだ行を削除し、残りの文字列を新しいメモリに保存する関数 */
char	*save_str(char *save)
{
	int		i;
	int		j;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')//現在の行の終わり（改行または終端）まで進む
		i++;
	if (!save[i])//もし文字列が終端に達していたら、全てのデータが読み込まれたので解放してNULLを返す
	{
		free(save);
		return (NULL);
	}
	new_save = malloc((ft_strlen(save) - i + 1) * sizeof(char));//残りの文字列用の新しいメモリ+NULLのメモリを確保
	if (!new_save)
	{
		free(save);  // メモリ確保に失敗した場合、元の文字列も解放
		return (NULL);
	}
	i++;  //改行文字をスキップ
	j = 0;
	while (save[i])//改行文字以降の残りの文字列をコピー
		new_save[j++] = save[i++];
	new_save[j] = '\0';  // 新しい文字列を終端
	free(save);  // 元の文字列を解放
	return (new_save);
}

/* supp_extract_line: saveから1行を抽出してlineにコピーする補助関数 */
static char	*supp_extract_line(char *save, char *line)
{
	int	i;

	i = 0;
	while (save[i] && save[i] != '\n')//改行まで、または終端まで文字をコピー
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')//改行文字があれば、それもコピー
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';  // 文字列を終端
	return (line);
}

/* extract_line: saveから1行を抽出し、新しい文字列として返す関数 */
static char	*extract_line(char *save)
{
	int		i;
	char	*line;
	int		flag;//改行文字の有無

	i = 0;
	flag = 0;
	if (!save[i])
		return (NULL);  // 空の文字列の場合はNULLを返す
	if (ft_strchr(save, '\n'))//改行文字があるかチェック（メモリ割り当てのサイズ決定に使用)
		flag = 1;
	while (save[i] && save[i] != '\n')//行の長さを計算
		i++;
	line = malloc((i + 1 + flag) * sizeof(char));//新しい行のためのメモリを確保（改行文字がある場合は追加の1バイトを確保
	if (!line)
		return (NULL);
	line = supp_extract_line(save, line);  // 行を抽出
	return (line);
}

/* supp_get_line: ファイルから読み込んでsaveを更新する補助関数 */
static char	*supp_get_line(int fd, char *save, char *buff)
{
	int		bytes;
	char	*tmp;

	while (!save || !ft_strchr(save, '\n'))//
	{
		bytes = read(fd, buff, BUFFER_SIZE);//ファイルからBUFFER_SIZEバイトずつ読み込む
		if (bytes == -1)//読み込みに成功したときは読み込んだバイト数を、失敗したときは-1を返します。
		{
			free(save); // 読み込みエラー時はsaveを解放
			return (NULL);
		}
		if (bytes == 0)//ファイル終端になると0を返す
			break;// ファイルの終端に達した場合
		buff[bytes] = '\0'; // 読み込んだデータを終端NULL止め
		tmp = ft_strjoin(save, buff);//読み込んだデータをsaveに追加
		if (!tmp)
		{
			free(save);  // メモリ確保失敗時はsaveを解放
			return (NULL);
		}
		free(save);//strajoin前の古いメモリを開放
		save = tmp;
	}
	return (save);
}

/* get_line: ファイルから1行を読み込む関数 */
static char	*get_line(int fd, char *save)
{
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));//読み込み用バッファのメモリを確保 
	if (!buff)
	{
		if (save)
			free(save);  // バッファ確保失敗時はsaveも解放
		return (NULL);
	}
	save = supp_get_line(fd, save, buff);//補助
	free(buff);  // 使用済みバッファを解放
	if (!save)
		return (NULL);
	return (save);
}

/* get_next_line: ファイルディスクリプタから次の行を取得する主要関数 */
char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[FOPEN_MAX];  // 複数のファイルディスクリプタ

	if (fd < 0 || BUFFER_SIZE <= 0)//無効なfdやBUFFER_SIZEをチェック 
		return (NULL);
	save[fd] = get_line(fd, save[fd]);//ファイルから一行読み込んでsaveを更新
	if (!save[fd])//読み込めていなかったら、リターン
		return (NULL);
	line = extract_line(save[fd]);  // saveから1行を抽出
	save[fd] = save_str(save[fd]);  // saveを更新（読み込んだ行を削除）
	return (line);
}
