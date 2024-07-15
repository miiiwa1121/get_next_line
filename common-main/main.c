/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:15:43 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/07/14 01:19:19 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_number;

	line_number = 1;
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", line_number++, line);
		free(line);
	}
	close(fd);
	return (0);
}
