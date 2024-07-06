/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:37:35 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/06 15:23:45 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdio.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
# endif

char *get_next_line(int fd);
char *read_all(int fd, char *s_str);
char *read_new_line(char *s_str);
char *other_new_str(char *s_str);
char *ft_strjoin(const char *s1, const char *s2);
size_t ft_strlen(const char *str);
char *ft_strchr(const char *s, int c);

#endif
