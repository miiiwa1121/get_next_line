/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:38:01 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/07 17:18:10 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
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
char *read_new_line(char *s_str)//s_strから一行を抜き出して新しいメモリを確保して返す
{
	char *str;
	int i;

	i = 0;
	if (!s_str[i])
		return (NULL);
	while(s_str[i] && s_str[i] != '\n')//終端または改行までのバイト数
		i++;
	str = (char *)malloc((i + 2) * sizeof(char));//s_strの改行もしくは終端までのサイズをmallocしてメモリを確保
	if(!str)
		return (NULL);
	i = 0;
	while(s_str[i] && s_str[i] != '\n')
	{
		str[i] = s_str[i];//strにs_strの改行もしくは終端までを代入		
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
	j=0;
	while(s_str[i] && s_str[i] != '\n')//終端または改行までのバイト数
		i++;
	if(!s_str[i])
	{
		free(s_str);
		return (NULL);
	}
	str = (char *)malloc((ft_strlen(s_str) - i + 1) * sizeof(char));//s_strの全体-s_strの一行分のサイズ+NULLをmalloc
	if(!str)
		return (NULL);
	i++;
	while(s_str[i])//改行の次から終端もしくは改行まで
		str[j++] = s_str[i++];//新メモリにコピー
	str[j] = '\0';
	free(s_str);
	return (str);
}
