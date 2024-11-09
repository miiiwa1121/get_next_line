/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:09:06 by jdecorte          #+#    #+#             */
/*   Updated: 2024/11/09 21:31:22 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_free(char *save, char *buff)
{
	char	*temp;

	temp = ft_strjoin(save, buff);
	free(save);
	return (temp);
}

char	*next_line(char *save)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(save) - i + 1), sizeof(char));
	if(!line)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		line[j++] = save[i++];
	free(save);
	return (line);
}

char	*get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if(!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] && save[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *save)
{
	char	*buff;
	int		bytes;

	if (!save)
		save = ft_calloc(1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if(!buff)
		return (ft_free(save));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		save = join_free(save, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_file(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	save = next_line(save);
	return (line);
}
