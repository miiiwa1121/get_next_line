/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:29:16 by resakai           #+#    #+#             */
/*   Updated: 2024/07/22 16:12:09 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*ft_strchr(const char *str, int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);

#endif