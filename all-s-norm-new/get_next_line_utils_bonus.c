/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:30:00 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/14 14:25:41 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

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
