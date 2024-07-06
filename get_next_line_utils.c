/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:38:01 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/06 16:18:45 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
    if (!s)
		return (NULL);
    while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
    return ((char *)s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*str_tmp;
	int		len;

	len = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str_tmp = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (str_tmp);
}

