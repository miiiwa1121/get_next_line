/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:37:35 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/07 16:37:26 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdio.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
# endif

char *get_next_line(int fd);
char *read_all(int fd, char *s_str);
char *ft_strchr(char *s, int c);
char *ft_strjoin(char *s1, char *s2);
size_t ft_strlen(char *str);
char *read_new_line(char *s_str);
char *extra_new_str(char *s_str);

#endif
