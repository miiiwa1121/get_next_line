#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd1, fd2, fd3;
    char *line;

    // 3つのテストファイルを読み取り専用で開く
    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);
    fd3 = open("test3.txt", O_RDONLY);

    // ファイルが正常に開けたかチェック
    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
    {
        printf("Error opening files\n");
        return (1);
    }

    // 5回のラウンドでファイルから読み取りを行う
    for (int i = 0; i < 13; i++)
    {
        printf("--- Round %d ---\n", i + 1);

        // ファイル1から1行読み取り
        line = get_next_line(fd1);
        printf("File 1: %s\n", line ? line : "EOF\n");
        free(line);  // 読み取った行のメモリを解放

        // ファイル2から1行読み取り
        line = get_next_line(fd2);
        printf("File 2: %s\n", line ? line : "EOF\n");
        free(line);  // 読み取った行のメモリを解放

        // ファイル3から1行読み取り
        line = get_next_line(fd3);
        printf("File 3: %s\n", line ? line : "EOF\n");
        free(line);  // 読み取った行のメモリを解放

        printf("\n");
    }
    // 開いたファイルをすべて閉じる
    close(fd1);
    close(fd2);
    close(fd3);

    return (0);
}