/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:38:01 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/07 18:28:48 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>

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

size_t ft_strlen(const char *str)
{
	const char *s;

	if (!str)
		return (0);
	s = str;
	while (*s)
		++s;
	return (size_t)(s - str);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	if (!s)
// 		return (NULL);
// 	while (*s != (char)c)
// 	{
// 		if (*s == '\0')
// 			return (NULL);
// 		s++;
// 	}
// 	return ((char*)s);
// }

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

// void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	size_t	i;
// 	char	*dst_cp;
// 	char	*src_cp;

// 	if (dst == src || n == 0)
// 		return (dst);
// 	dst_cp = (char *)dst;
// 	src_cp = (char *)src;
// 	i = 0;
// 	while (i < n)
// 	{
// 		dst_cp[i] = src_cp[i];
// 		i++;
// 	}
// 	return (dst);
// }

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *d;
	const unsigned char *s;

	d = dst;
	s = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}

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

char *ft_strjoin(char const *s1, char const *s2)
	{
	char *result;
	size_t 	len1; 
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	return (result);
	}
