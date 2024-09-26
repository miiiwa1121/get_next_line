/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:14:11 by jdecorte          #+#    #+#             */
/*   Updated: 2024/09/26 15:42:43 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *string, int key )
{
	char	*str;

	str = (char *)string;
	while (*str != key && *str != '\0')
		str++;
	if (*str == key)
		return (str);
	else
		return (NULL);
}

size_t	ft_strlen(const char *string)
{
	int	count;

	count = 0;
	while (string[count])
		count++;
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		allsize;
	int		i;
	int		j;

	allsize = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (allsize + 1));
	if (!result || !s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[allsize] = '\0';
	return (result);
}

void	ft_bzero(void *s, size_t n)//どんな型で渡されても汎用的に動作するために、void* 型で受け取る
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)//先頭からnまで0埋め
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*result;

	result = malloc(count * size);
	if (!result)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}
