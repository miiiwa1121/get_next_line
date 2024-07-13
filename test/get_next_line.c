/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:36:59 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/07 16:45:19 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
//#include <stdio.h>
//#include <fcntl.h>

char 	*read_all(int fd, char *s_str)
{
	char *buff;
	int read_byte;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!buff)
		return (NULL);
	read_byte = 1;
	while(!ft_strchr(s_str,'\n') && read_byte != 0)
	{
		read_byte = read(fd, buff ,BUFFER_SIZE);
		if(read_byte  == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[read_byte] = '\0';
		s_str = ft_strjoin(s_str, buff);
	}
	free(buff);
	return (s_str);
}

char *get_next_line(int fd)
{
	static char *s_str;
	char *line;
	
 	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s_str = read_all(fd, s_str);
	if(!s_str)
		return (NULL);
	line = read_new_line(s_str);
	s_str = extra_new_str(s_str);
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
