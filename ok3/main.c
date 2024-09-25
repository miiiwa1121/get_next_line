/* main.c (ノンボーナス版) */
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int fd;
    char *line;
    int line_count = 0;

    // 単一のファイルを開く
    fd = open("test1.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Error opening file\n");
        return (1);
    }

    // ファイルから行を読み取り、一行ずつ表示する
    printf("Reading from test1.txt:\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        line_count++;
        printf("Line %d: %s\n", line_count, line);
        
        // 行の最後に改行がない場合は、出力に改行を追加
        if (line[0] != '\0' && line[strlen(line) - 1] != '\n')
            printf("\n");
        
        free(line);
    }

    close(fd);
    return (0);
}