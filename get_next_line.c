/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/05 11:53:13 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
include "get_next_line.h"

char *get_next_line(int fd)
{
	char	buff[100 + 1];
	int		rc;
//エラー処理
 	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
//開いたファイルのデータを一文字ずつ改行まで読む
//開いたファイルのデータサイズ分をmallocして、格納して返す

	while()
	{
		if(fd >= 0 && )
			rc = read(fd,buff,100);
	}
}

#include<stdio.h>

int main(void)
{
	int fd;
	int i;
	const char *filename;

	filename = "test1.txt";
	fd = open(filename,O_RDONLY);
	if(fd < 0)
	{
		printf("openエラー");
		return (NULL);
	}
	while(i < 2){
		get_next_line(fd);
	}
	close(fd);
	return (0);
}


// #include "get_next_line.h"
// #include <unistd.h>
// #include <stdio.h>
// #include <fcntl.h>

// char	*ft_get_line(char *left_str)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	if (!left_str[i])
// 		return (NULL);
// 	while (left_str[i] && left_str[i] != '\n')
// 		i++;
// 	str = (char *)malloc(sizeof(char) * (i + 2));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (left_str[i] && left_str[i] != '\n')
// 	{
// 		str[i] = left_str[i];
// 		i++;
// 	}
// 	if (left_str[i] == '\n')
// 	{
// 		str[i] = left_str[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// char	*ft_new_left_str(char *left_str)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	while (left_str[i] && left_str[i] != '\n')
// 		i++;
// 	if (!left_str[i])
// 	{
// 		free(left_str);
// 		return (NULL);
// 	}
// 	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));
// 	if (!str)
// 		return (NULL);
// 	i++;
// 	j = 0;
// 	while (left_str[i])
// 		str[j++] = left_str[i++];
// 	str[j] = '\0';
// 	free(left_str);
// 	return (str);
// }


// char	*ft_read_to_left_str(int fd, char *left_str)
// {
// 	char	*buff;
// 	int		rd_bytes;

// 	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buff)
// 		return (NULL);
// 	rd_bytes = 1;
// 	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
// 	{
// 		rd_bytes = read(fd, buff, BUFFER_SIZE);
// 		if (rd_bytes == -1)
// 		{
// 			free(buff);
// 			return (NULL);
// 		}
// 		buff[rd_bytes] = '\0';
// 		left_str = ft_strjoin(left_str, buff);
// 	}
// 	free(buff);
// 	return (left_str);
// }

// char	*get_next_line(int fd)
// {
// 	char		*line;
// 	static char	*left_str;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (0);
// 	left_str = ft_read_to_left_str(fd, left_str);
// 	if (!left_str)
// 		return (NULL);
// 	line = ft_get_line(left_str);
// 	left_str = ft_new_left_str(left_str);
// 	return (line);
// }

// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	fd1 = open("test1.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	fd3 = open("test3.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 7)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		line = get_next_line(fd2);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		line = get_next_line(fd3);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
