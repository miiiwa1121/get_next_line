# get_next_line

main
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=10 main.c get_next_line.c get_next_line_utils.c -o get_next_line

./get_next_line ../text1.txt

leaks
valgrind --leak-check=full --show-leak-kinds=all -s ./get_next_line


bonus
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c get_next_line_bonus.h -o get_next_line_bonus

./get_next_line_bonus test1.txt test2.txt test3.txt

leaks
valgrind --leak-check=full --show-leak-kinds=all -s ./get_next_line_bonus



fd = 開かれたファイルを表す「番号札」


テキストファイルに人間が

12345678
23456789
3243456768790898

と記入しても
コンピューター視点では

12345678\n23456789\n3243456768790898\0

のように見えている

今回の例で行くとバッファサイズを5とすると、

一回目　12345
二回目　678\n2

と読み込まれ、残りは

3456789\n3243456768790898\0

となるが、
一行ずつ出力するには\n以降の数字を取り除いて、取り除いた数字をファイル全体の数字に戻す必要がある

つまり、

23456789\n3243456768790898\0

になる

バッファサイズ分読み込んで、/n以上、/n以下で分けて、出力、保存する。
これらを、バッファサイズ分読み込んだ時点で改行が見つからないまで繰り返す。

3456789\n3243456768790898\0

34567
89\n32

43456768790898\0

3243456768790898\0

32434
56768
79089
8\0

\0

8\0を読み込んだ時点で改行が見つからなかったので、

next_lineの

	if (!save[i])//改行が見つからない
	{
		free(save);
		return (NULL);
	}

にて、

解放returnして、終了
