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

＜手順＞

テキストファイルに人間が

12345678
23456789
3243456768790898

と記入しても
コンピューター視点では

12345678\n23456789\n3243456768790898\0

のように見えている(のかな)

今回の例で行くとバッファサイズを5とすると、

一回目　12345
二回目　678\n2\0

と読み込んだ値の中に改行が見つかるで読み込まれる。

残り　3456789\n3243456768790898\0

となるが、
一行ずつ出力するには\n以降の数字を取り除いて、取り除いた数字をファイル全体の数字に戻す必要がある

つまり、

一回目　12345
二回目　678\n\0

残り　23456789\n3243456768790898\0

になる

バッファサイズ分読み込んで、/n以上、/n以下で分けて、出力、保存する。
これらを、バッファサイズ分読み込んだ時点で改行が見つからないまで繰り返す。

残り　23456789\n3243456768790898\0

一回目 23456
二回目 789\n3\0

残り　243456768790898\0

一回目 23456
二回目 789\n\0

残り　3243456768790898\0

一回目 32434
二回目 56768
三回目 79089
四回目 8\0

残り\0

8\0を読み込んだ時点で改行が見つからなかったので、

next_lineの

	if (!save[i])//終端である　＝　改行が見つからない
	{
		free(save);
		return (NULL);
	}

にて、

解放 & returnして、終了

＜用語＞

fd = 開かれたファイルを表す「番号札」
FOPEN_MAX = プログラムが同時に開くことを保証される標準ストリーム数の上限
static = ローカル変数の場合/関数が終了しても値が保持される
static = グローバル変数や関数の場合/変数や関数のスコープが「ファイル内に限定」され、他のファイルからアクセスできなくなる「内部リンケージ」

問１
メモリをゼロ埋めする意味は何？
A.
未初期化メモリの防止:
メモリをゼロ埋めすることで、未初期化のメモリ領域にアクセスする際の不具合を防ぎます。特に、文字列や配列を扱う場合、ゼロで初期化されたメモリは、後で空文字列や適切な終了条件として扱われます。

問２
ft_bzeroでvoid型で引数を受け取っているのはなぜ？
A.
どんな型で渡されても汎用的に動作するために、void* 型で受け取る


問３
read_fileで

if (!save)
		save = ft_calloc(1, 1);

をしている理由は何？
A.
初期状態の確保:
saveがNULLである場合、これはまだメモリが確保されておらず、データが保存されていない状態を示します。ft_calloc(1, 1)を呼び出すことで、1バイトのメモリを確保し、その内容をゼロで初期化します。

後続の操作のための準備:
read_file関数では、ファイルからデータを読み込む際に、saveに新しいデータを追加していくことになります。この時、saveがNULLであると、データを結合するためのベースとなるメモリが存在しないため、エラーが発生する可能性があります。初期化することで、saveが空の文字列として扱われ、後続の処理がスムーズに進むようになります。

問４
readコマンドは、どこまで読んだかを記憶するのですか？
A.
readコマンドや多くのファイル読み込み関数は、どこまで読んだかを記憶します。これは「ファイルポインタ」または「ファイル位置インジケータ」と呼ばれる仕組みを使用しています。
ファイルポインタの特徴：

現在位置の追跡：
ファイルポインタは、ファイル内の現在の読み取り/書き込み位置を追跡します。
自動更新：
readコマンドが実行されるたびに、読み取ったバイト数だけファイルポインタが自動的に更新されます。
次の読み取り位置：
次のread操作は、前回の操作で終了した位置から開始されます。
ファイルディスクリプタとの関連：
ファイルポインタは、オープンされたファイルのファイルディスクリプタに関連付けられています。
シーク操作：
多くのシステムでは、lseek()のような関数を使用してファイルポインタを明示的に移動させることもできます。


問５
標準ストリーム数は何？
A.
C言語を含む多くのプログラミング環境で提供される、データの入出力に関する基本的な仕組みです。これらはプログラムが起動時に自動的に初期化され、特定の用途に使われます。

標準ストリーム数について
C言語のプログラムでは、少なくとも以下の3つの標準ストリームが最初から開いています：
標準入力 (stdin)
標準出力 (stdout)
標準エラー出力 (stderr)
これらはプログラム起動時に自動的に開かれるストリームです。

FOPEN_MAX の保証の意味
FOPEN_MAX が指すのは、**これらの標準ストリームを含めた「同時に開くことができるファイルストリームの最大数」**です。たとえば、FOPEN_MAX が20に設定されている場合、次のことが保証されます：
プログラムが3つの標準ストリーム (stdin, stdout, stderr) を使用している状態でも、さらに17個のストリームを開くことができる。
これを超えるファイルストリームを開こうとすると、標準ライブラリの関数（例: fopen）がエラーを返します。

問６
fdとFOPEN_MAXの関係は何？
A.
標準ストリームとファイルディスクリプタの対応
C言語の標準ストリーム (stdin, stdout, stderr) は、低レベルのファイルディスクリプタに直接対応しています。

標準ストリーム	ファイルディスクリプタ	用途
stdin	0	標準入力
stdout	1	標準出力
stderr	2	標準エラー出力

これらのディスクリプタは、プログラム起動時にOSによって自動的に割り当てられ、常に利用可能な状態にあります。

問６
get_lineのline = ft_calloc(i + 2, sizeof(char));の+2は何
A.
改行文字 \n のための1バイト
文字列終端の \0 のための1バイト