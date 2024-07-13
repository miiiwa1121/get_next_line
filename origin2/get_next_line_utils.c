/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:38:01 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/11 15:56:33 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t ft_strlen(const char *str)
{
	size_t len;

	if (!str)
		return (0);
	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

char *ft_strchr(const char *s, int c)
{
	char ch;

	ch = (char)c;
	while (1)
	{
		if (*s == ch)
			return (char *)s;
		if (*s == '\0')
			return (NULL);
		s++;
	}
}

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *d;
	const unsigned char *s;
	size_t i;

	d = dst;
	s = src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	char *result;
	size_t len1; 
	size_t len2;
	size_t total_len;

	if (!s1 && !s2)
		return (NULL);
	len1 = s1 ? ft_strlen(s1) : 0;
	len2 = s2 ? ft_strlen(s2) : 0;
	total_len = len1 + len2;
	result = (char *)malloc(total_len + 1);
	if (!result)
		return (NULL);
	if (s1)
		ft_memcpy(result, s1, len1);
	if (s2)
		ft_memcpy(result + len1, s2, len2);
	result[total_len] = '\0';
	return (result);
}
