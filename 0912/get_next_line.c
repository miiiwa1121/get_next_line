/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 02:15:30 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/09/12 04:46:41 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		str++;
		count++;
	}
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (1)
	{
		if (*s == ch)
			return ((char *)s);
		if (*s == '\0')
			return (NULL);
		s++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	len = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (str);
}

char	*save_str(char *save)
{
	int		i;
	int		j;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (NULL);
	new_save = malloc((ft_strlen(save) - i + 1) * sizeof(char));
	if (!new_save)
	{
		free(new_save);
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

char	*get_line(int fd,char*save)
{
	char	*buff;
	int		bytes;
	char	*tmp;


	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (!save || !ft_strchr(save, '\n'))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		tmp = ft_strjoin(save, buff);
		if (!tmp)
			return (NULL);
		free(save);
		save = tmp;
	}
	return (save);
}


char	*get_next_line(int fd)
{
	char	*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(fd, save);
	if (!save)
	{
		free(save);
		return (NULL);
	}
	save = save_str(save);
	if (!save)
	{
		free(save);
		return (NULL);
	}
	return (line);
}
