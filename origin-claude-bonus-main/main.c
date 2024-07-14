/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:30:00 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/14 14:40:17 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 3

int main(int argc, char **argv)
{
    int fd[MAX_FILES];
    char *line;
    int i, active_files;

    if (argc < 2)
    {
        printf("Usage: %s <file1> [file2] [file3]\n", argv[0]);
        return 1;
    }

    active_files = argc - 1 > MAX_FILES ? MAX_FILES : argc - 1;

    for (i = 0; i < active_files; i++)
    {
        fd[i] = open(argv[i + 1], O_RDONLY);
        if (fd[i] == -1)
        {
            printf("Cannot open file %s\n", argv[i + 1]);
            while (i > 0)
                close(fd[--i]);
            return 1;
        }
    }

    while (active_files > 0)
    {
        for (i = 0; i < active_files; i++)
        {
            line = get_next_line(fd[i]);
            if (line)
            {
                printf("File %d: %s", i + 1, line);
                free(line);
            }
            else
            {
                printf("File %d: End of file\n", i + 1);
                close(fd[i]);
                fd[i] = fd[active_files - 1];
                active_files--;
                i--;
            }
        }
        printf("\n");
    }

    return 0;
}