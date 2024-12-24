# get_next_line

## English Version

### Project Structure
```
.
├── README.md
├── get_next_line.c
├── get_next_line.h
├── get_next_line_bonus.c
├── get_next_line_bonus.h
├── get_next_line_utils.c
├── get_next_line_utils_bonus.c
├── main.c
├── main_bonus.c
├── test1.txt
├── test2.txt
└── test3.txt

1 directory, 15 files
```

### Build and Run

#### Main Program
1. Compile:
   ```bash
   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=10 main.c get_next_line.c get_next_line_utils.c -o get_next_line
   ```
2. Run:
   ```bash
   ./get_next_line test1.txt
   ```
3. Memory Leak Check:
   ```bash
   valgrind --leak-check=full --show-leak-kinds=all -s ./get_next_line
   ```

#### Bonus Program
1. Compile:
   ```bash
   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -o get_next_line_bonus
   ```
2. Run:
   ```bash
   ./get_next_line_bonus test1.txt test2.txt test3.txt
   ```
3. Memory Leak Check:
   ```bash
   valgrind --leak-check=full --show-leak-kinds=all -s ./get_next_line_bonus
   ```

### Explanation of Behavior
- Text files written by humans appear as:
  ```
  12345678
  23456789
  3243456768790898
  ```
  To the computer, they look like:
  ```
  12345678\n23456789\n3243456768790898\0
  ```

- Example with BUFFER_SIZE = 5:
  - First read: `12345`
  - Second read: `678\n2\0`
  - The program detects a newline (`\n`) and processes the first line.

- Remaining data: `23456789\n3243456768790898\0`
  - This process continues until all lines are read.

### Key Concepts
#### Terms
- **fd**: File descriptor, a unique number representing an open file.
- **FOPEN_MAX**: Maximum number of files a program can open simultaneously.
- **static**: Used to retain variable values or restrict variable/function scope within a file.

#### Buffer Behavior
- The buffer reads a fixed size and splits lines based on newlines (`\n`). Remaining data is saved for subsequent reads.

---

### Questions and Answers

#### Q1. Why zero out memory?
- **Purpose:** Prevent issues with uninitialized memory.
- **Benefit:** Ensures memory starts in a consistent state, particularly for strings and arrays.

#### Q2. Why does `ft_bzero` use `void*`?
- **Reason:** Allows for flexible use with different data types.

#### Q3. Why initialize `save` with `ft_calloc(1, 1)`?
- **Purpose:** Allocate initial memory if `save` is `NULL`. Prepares for subsequent concatenations.

#### Q4. Does `read` remember its position?
- **Yes:** It uses a file pointer to track progress, automatically updated after each call.

#### Q5. What is the standard stream limit?
- **Streams:** `stdin`, `stdout`, `stderr` are always open. Additional streams are limited by `FOPEN_MAX`.

#### Q6. What does `+2` in `ft_calloc(i + 2, sizeof(char))` do?
- **Purpose:** Reserves space for a newline (`\n`) and a null terminator (`\0`).

---

## Japanese Version

### ビルドと実行

#### メインプログラム
1. コンパイル:
   ```bash
   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=10 main.c get_next_line.c get_next_line_utils.c -o get_next_line
   ```
2. 実行:
   ```bash
   ./get_next_line test1.txt
   ```
3. メモリリークチェック:
   ```bash
   valgrind --leak-check=full --show-leak-kinds=all -s ./get_next_line
   ```

#### ボーナスプログラム
1. コンパイル:
   ```bash
   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -o get_next_line_bonus
   ```
2. 実行:
   ```bash
   ./get_next_line_bonus test1.txt test2.txt test3.txt
   ```
3. メモリリークチェック:
   ```bash
   valgrind --leak-check=full --show-leak-kinds=all -s ./get_next_line_bonus
   ```

### 動作の説明
- 人間が記述するテキスト:
  ```
  12345678
  23456789
  3243456768790898
  ```
  コンピュータ視点では次のように見えます:
  ```
  12345678\n23456789\n3243456768790898\0
  ```

- BUFFER_SIZE = 5 の例:
  - 1回目の読み取り: `12345`
  - 2回目の読み取り: `678\n2\0`
  - プログラムは改行を検出し、最初の行を処理します。

- 残りデータ: `23456789\n3243456768790898\0`
  - このプロセスをすべての行が読み取られるまで繰り返します。

### 重要な概念
#### 用語
- **fd**: ファイルディスクリプタ。開かれたファイルを表す一意の番号。
- **FOPEN_MAX**: プログラムが同時に開くことができるファイル数の上限。
- **static**: 変数の値を保持したり、スコープをファイル内に限定する修飾子。

#### バッファの挙動
- 固定サイズのバッファを使用し、改行で行を分割。残りのデータは次回の読み取りに保存。

---

### 質問と回答

#### Q1. メモリをゼロ埋めする理由は？
- **目的:** 未初期化メモリによる問題を防ぐため。
- **利点:** 一貫した状態でメモリを利用可能に。

#### Q2. `ft_bzero` が `void*` を使う理由は？
- **理由:** 型に依存せず汎用的に利用するため。

#### Q3. なぜ `save` を `ft_calloc(1, 1)` で初期化する？
- **目的:** `save` が NULL の場合にメモリを確保し、データ結合の基盤を用意するため。

#### Q4. `read` コマンドは読み取り位置を記憶する？
- **はい:** ファイルポインタを使用して進行状況を追跡します。

#### Q5. 標準ストリームの上限は？
- **ストリーム:** `stdin`、`stdout`、`stderr` は常に開かれている。追加ストリームは `FOPEN_MAX` に制限される。

#### Q6. `ft_calloc(i + 2, sizeof(char))` の `+2` の意味は？
- **目的:** 改行 (`\n`) とヌル終端 (`\0`) 用のバイトを確保するため。

