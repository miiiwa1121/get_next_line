#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	const char	*s;

	if (!str)
		return (0);
	s = str;
	while (*s)
		++s;
	return ((size_t)(s - str));
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

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	while (*s)
		*dup++ = *s++;
	*dup = '\0';
	return (dup - len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
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


static char	*supp_extract_line(char *save, char *line)
{
	int	i;

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

static char	*extract_line(char *save)
{
	int		i;
	char	*line;
	int		flag;

	i = 0;
	flag = 0;
	if (!save[i])
		return (NULL);
	if (ft_strchr(save, '\n'))
		flag = 1;
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc((i + 1 + flag) * sizeof(char));
	if (!line)
		return (NULL);
	line = supp_extract_line(save, line);
	return (line);
}

static char	*supp_get_line(int fd, char *save, char *buff)
{
	int		bytes;
	char	*tmp;

	while (!save || !ft_strchr(save, '\n'))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(save);
			return (NULL);
		}
		if (bytes == 0)
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
	}
	return (save);
}

static char	*get_line(int fd, char *save)
{
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
	{
		if (save)
			free(save);
		return (NULL);
	}
	save = supp_get_line(fd, save, buff);
	free(buff);
	if (!save)
		return (NULL);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = get_line(fd, save);
	if (!save)
		return (NULL);
	line = extract_line(save);
	save = save_str(save);
	return (line);
}
