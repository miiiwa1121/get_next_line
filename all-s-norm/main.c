#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("/Users/mtsubasa/francinette/tests/get_next_line/fsoares/1char.txt",  O_RDWR);
	char *line = get_next_line(fd);
	printf("%lu %s\n", strlen(line), line);
	line = get_next_line(fd);
	printf("%lu %s\n", strlen(line), line);
	line = get_next_line(fd);
	printf("%lu %s\n", strlen(line), line);
}