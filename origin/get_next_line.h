/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:37:35 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/07 17:34:01 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdio.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

char *get_next_line(int fd);
char *get_line(int fd, char *s_str);
char *extract_line(char *save);
char *save_str(char *save);
char *ft_strjoin(const char *s1, const char *s2);
size_t ft_strlen(const char *str);
char *ft_strchr(const char *s, int c);

#endif
