/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:58:27 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/22 16:12:48 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

char	*ft_strchr(const char *str, int c)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == (char)c)
			return ((char *)&str[index]);
		index++;
	}
	if ((char)c == '\0')
		return ((char *)&str[index]);
	return (NULL);
}

char	*ft_strcat(char *dest, const char *src)
{
	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	index;

	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}
