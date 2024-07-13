/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:38:01 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/07 16:43:36 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

char *read_new_line(char *s_str)
{
	char *str;
	int i;

	i = 0;
	if (!s_str[i])
		return (NULL);
	while(s_str[i] && s_str[i] != '\n')
		i++;
	str = (char *)malloc((i + 2) * sizeof(char));
	if(!str)
		return (NULL);
	i = 0;
	while(s_str[i] && s_str[i] != '\n')
	{
		str[i] = s_str[i];
		i++;
	}
	if(s_str[i] == '\n')
	{
		str[i] = s_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *extra_new_str(char *s_str)
{
	int i;
	int j;
	char *str;

	i = 0;
	while(s_str[i] && s_str[i] != '\n')
		i++;
	if(!s_str[i])
	{
		free(s_str);
		return (NULL);
	}
	str = (char *)malloc((ft_strlen(s_str) - i + 1) * sizeof(char));
	if(!str)
		return (NULL);
	i++;
	j = 0;
	while(s_str[i])
		str[j++] = s_str[i++];
	str[j] = '\0';
	free(s_str);
	return (str);
}
// #include <stddef.h>
// #include <stdlib.h>

// size_t	ft_strlen(const char *str)
// {
// 	size_t	count;

// 	count = 0;
// 	if (!str)
// 		return (0);
// 	while (str[count] != '\0')
// 		count++;
// 	return (count);
// }

// char	*ft_strchr(const char *s, int c)
// {
//     if (!s)
// 		return (NULL);
//     while (*s != (char)c)
// 	{
// 		if (*s == '\0')
// 			return (NULL);
// 		s++;
// 	}
//     return ((char *)s);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	char	*str_tmp;
// 	int		len;

// 	len = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	str = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!str)
// 		return (NULL);
// 	str_tmp = str;
// 	while (*s1)
// 		*str++ = *s1++;
// 	while (*s2)
// 		*str++ = *s2++;
// 	*str = '\0';
// 	return (str_tmp);
// }
