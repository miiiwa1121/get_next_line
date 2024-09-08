# get_next_line

main
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=10 main.c get_next_line.c get_next_line_utils.c -o get_next_line

./get_next_line ../text1.txt

leaks
valgrind --leak-check=full --show-leak-kinds=all ./get_next_line


bonus
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c get_next_line_bonus.h -o get_next_line_bonus

./get_next_line_bonus test1.txt test2.txt test3.txt

leaks
valgrind --leak-check=full --show-leak-kinds=all ./get_next_line_bonus



fd = 開かれたファイルを表す「番号札」