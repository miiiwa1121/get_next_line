/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/07 16:34:34 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

char 	*read_all(int fd, char *s_str)//fdのデータをすべてs_strに格納
{
	char *buff;
	int read_byte;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));//BUFFER_SIZE+NULLのメモリを確保
	if(!buff)
		return (NULL);
	read_byte = 1;
	while(!ft_strchr(s_str,'\n') && read_byte != 0)//s_strに改行が見つからない、かつ、ファイルの終端に達していない
	{
		read_byte = read(fd, buff ,BUFFER_SIZE);//BUFFER_SIZE分buffに格納し、文字数（バイト数）を返すが、ファイル終端になると0を返す
		if(read_byte  == -1)
		{//readに失敗したら
			free (buff);
			return (NULL);
		}
		buff[read_byte] = '\0';//buffの最後尾をNULL止め
		s_str = ft_strjoin(s_str, buff);//s_strにbuffを結合
	}
	free(buff);
	return (s_str);
}

char *get_next_line(int fd)
{
	static char *s_str;
	char *line;
	
 	if (fd < 0 || BUFFER_SIZE <= 0)//エラー処理
		return (NULL);
	s_str = read_all(fd, s_str);//fdのデータをメモリを確保してs_strに格納
	if(!s_str)
		return (NULL);
	line = read_new_line(s_str);//fdのデータを一行抜き出して新メモリに格納して返す。　
	s_str = extra_new_str(s_str);//read_line以外のデータを抜き出して新メモリに格納して返す
	return (line);
}

// #include<stdio.h>

// int main(void)
// {
// 	int fd;
// 	int i;
// 	char *line;
// 	const char *filename;

// 	i = 0;
// 	filename = "test2.txt";
// 	fd = open(filename,O_RDWR);
// 	if(fd < 0)
// 	{
// 		printf("openエラー");
// 		return (1);
// 	}
// 	while(i < 7)
// 	{
// 		line = get_next_line(fd);
// 		printf("line [%d]: %s\n", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
