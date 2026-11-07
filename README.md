*This project has been created as part
of the 42 curriculum by rutakano.*

# Get_Next_line
## 概要
この課題では、ファイルディスクリプタによって指定されたファイルを一度に一行ずつ読み込むget_next_line()を作ることが目的である。get_next_line()は正常にファイルから一行を読むことができた場合、改行を示す\nを含む一行を返す（ただし、ファイルの一番最後の行の場合を除く）。また、ファイルの読み込みエラーなどを含む問題が生じた場合や、ファイルの内容をすべて読み込んだ場合は返り値としてNULLを返す。

また、本プロジェクトは、ボーナスの内容も含む。複数の指定されたファイルからそれぞれ一度に一行ずつ読み込むことができる仕様である。

### 各関数について
#### get_next_line.c の関数
- get_next_line
    - ファイルディスクリプタによって指定されたファイルを一度に一行だけ読み、その行の内容を改行'\n'を含めて返す（エラーや既に全ての内容を読んだ場合はNULLを返す）。
- ft_get_line
    - get_next_lineから呼ばれる関数。ファイルディスクリプタとread関数で用いるバッファーbuff、余剰surplusを引数として、
    余剰または新たに読み込まれた内容から一行を読み込んで返り値として返す。
- copy_source
    - 渡された文字列（余剰またはバッファー）から、'\n'まで（もしくは終端まで）をコピーする関数。'\n'が見つかり、一行が読み取れた場合は返り値として１を返し、そうでない場合は０を返す。
- ft_make_surplus
    - 余剰が始まる先頭のポインタを第一引数として受け取り、第二引数としてその長さを受け取る。それらから新たな余剰を作り、返す関数。これによって作られた余剰は必ず'\0'文字で終端する。

#### get_next_line_utils.c の関数
- ft_realloc
    - 配列を受け取り、それに対して元の大きさ+BUFFER_SIZE分の領域
    を確保し、それに既存の内容を入れる。元の領域は解放する。
- ft_strlen
    - 文字列を受け取り、その文字数を返す関数。引数として受け取る文字列str(char *型)は'\0'で終端されていることを前提としている。
- ft_free_candidates
    - それまでに確保した領域を受け取り、NULLでない場合、その領域を解放する関数。引数として受け取るのは、read関数で用いるbuff、get_next_lineで読んだ一行を格納するためのline、余剰を示すsurplusの３つのポインタである。
- find_file_node
    - ファイルディスクリプタとその余剰を保持するためのノードを持った連結リストについて、指定されたファイルディスクリプタが既にノードとして存在する場合そのノードを返す。また、該当のノードが存在しない場合、新たなノードを作成し連結リストに繋げ、そのノードを返す。
- lst_add_back
    - 与えられた連結リストの末尾に指定したノードを繋げるfind_file_nodeの補助関数。

また、接尾辞_bonusを含む.cファイルは以上のオリジナルと全く同じ内容である。
## 使用方法
gitから本プロジェクトに該当するリポジトリをクローンします。
```c
git clone 
```
get_next_line()で読むためのファイルを、クローンしたディレクトリ内に用意してください。

一つ前のコミットから、テスト用に用意された３つのtxtファイルを利用することができます。
```c
git show HEAD^ pawmot.txt > pawmot.txt
git show HEAD^ rui.txt > rui.txt
git show HEAD^ takano.txt > takano.txt
```
Makefileを用いて、get_next_line.cとget_next_liine_utils.cをコンパイルします。以下から、どれか一つのコマンドを利用することでコンパイルが可能です。
```c
make
make all
make get_next_line
```
コンパイルを行なって、できた実行ファイルget_next_lineを実行します。
```c
 ./get_next_line
```

また、bonus課題についてはMakefileのボーナスルールで使用することができます。
```c
make bonus
```
コンパイルを行なって、できた実行ファイルget_next_line_bonusを実行します。
```c
 ./get_next_line_bonus
```

```c
 ./get_next_line_bonus
```
出力結果と読んだファイルの内容を照らし合わせ、確認を行なってください。

## リソース
プログラミングに関する情報を蓄積する雑記帳 Prog.さな雑記
https://progzakki.sanachan.com/program-lang/c/how-to-use-read/

### AIの使用について
本プロジェクトのプログラムについて、一切AIによって書かれたものはなく、全てのコードがrutakano（イントラ名）によって作成されたものである。なお、vsCode上におけるデバッグ環境の整備、README.mdの英訳についてAIを用いて行なった。

## アルゴリズムについて
read()関数で指定のファイルからBUFFER_SIZE文読み込み、一行を抽出するにあたって、read()で読んだ分から余剰が生じることがある。

例えば、buffをread()で読み込むバッファーとして、以下のように読みとりがされたとき、"Hello\n"が一行とみなされ、"42Tokyo"という余剰が生じる。
```c
buff = "Hello\n42Tokyo";
```
ここで生じた余剰は通常関数の終了時に失われてしまう。
この内容を、再度関数を呼び出したときに利用できるようにするため、get_next_line()で以下の構造体を用いた静的な連結リストを宣言した。なお、上の構造体が定義されているのはget_next_line_h (get_next_line_bonus.h)である。
```c
//構造体
typedef struct s_file
{
	char	*surplus;
	int		fd;
	struct s_file	*next;
}	t_file;


char	*get_next_line(int fd)
{
	static t_file	**files;
            ：
            ：
}
```
このような連結リストを静的な変数として利用したのは、ボーナス課題を踏まえ、さまざまなファイルディスクリプタに対して、それぞれの余剰を対応させて保持しておくためである。
連結リストfilesにノードの連結を行なっているのはfind_file_node()とlst_add_back()である。
この連結リストを用いて、ft_get_line()から指定のファイルの一行を実際に抽出している。

## 技術選択
### BUFFER_SIZEの指定について
コンパイル時に "-D BUFFER_SIZE=n"というコンパイラコールでマクロBUFFER_SIZEの値を指定することができる。この数が負または０以下またはread()関数で読むことができる上限であるSSIZE_MAX以上の場合、ただちにNULLを返す。  
また、この範囲出なかった場合にもread関数が失敗した場合はbuffとlineの２つの領域を解放する。
### get_next_lineで読み取る一行の文字数の上限について
読み取る一行がSIZE_MAXを超えてしまう場合について、ft_realloc()関数でlineの大きさの拡張をする際にエラー処理をしている。

### メモリの処理について
read()関数で読み取るために用意したバッファーbuffはget_next_line()終了時に開放する。
また、読み取った一行を格納するlineは読み取り成功時にはget_next_line()上では解放しない。テストで用意したmain関数ではprintfでlineの内容を表示させたあとそのメモリ領域を解放している。
また、読み取ったファイルの余剰を示すsurplusは静的な連結リストであるlists(t_list **型)のメンバ変数だが、read()関数が失敗した場合にのみsurplusをfree()する。

staticな変数はmain関数終了時に解放されるため、
メモリーリークは生じない。

---

# English Translation

## Overview
The goal of this project is to implement `get_next_line()`, a function that reads a file specified by a file descriptor one line at a time. When a line is read successfully, `get_next_line()` returns that line, including the newline character `\n` if present. If an error occurs, including a file read error, or the entire file has been read, the function returns `NULL`.

This project also includes the bonus requirements: it supports reading one line at a time from multiple files, keeping track of each file independently.

### Functions

#### Functions in get_next_line.c
- `get_next_line`
    - Reads one line from the file specified by the file descriptor and returns it, including the newline character `\n`. Returns `NULL` if an error occurs or the entire file has already been read.
- `ft_get_line`
    - Called by `get_next_line`. Takes a file descriptor, the buffer `buff` used by `read()`, and the leftover data `surplus` as arguments. Builds and returns a line from the leftover data or newly read data.
- `copy_source`
    - Copies characters from the given string (either the leftover data or the buffer) through the first `\n`, or to the end of the string. Returns `1` if a newline is found and a complete line has been read; otherwise, returns `0`.
- `ft_make_surplus`
    - Takes a pointer to the beginning of the leftover data as its first argument and its length as its second argument. Creates and returns a new string containing that data. The resulting string is always terminated with `\0`.

#### Functions in get_next_line_utils.c
- `ft_realloc`
    - Takes an array, allocates a new memory block with the original size plus `BUFFER_SIZE`, and copies the existing contents into it. Frees the original memory block.
- `ft_strlen`
    - Returns the number of characters in a string. Assumes that the argument `str` (of type `char *`) is terminated with `\0`.
- `ft_free_candidates`
    - Frees previously allocated memory blocks if their pointers are not `NULL`. Takes three pointers: `buff`, the buffer used by `read()`; `line`, which stores the line read by `get_next_line()`; and `surplus`, which stores the leftover data.
- `find_file_node`
    - Searches a linked list whose nodes store file descriptors and their leftover data. Returns the node for the specified file descriptor if it already exists. Otherwise, creates a new node, appends it to the list, and returns it.
- `lst_add_back`
    - A helper function for `find_file_node` that appends the specified node to the end of the given linked list.

The `.c` files with the `_bonus` suffix contain exactly the same code as their original counterparts.

## Usage
Clone this project's Git repository:
```sh
git clone
```
Prepare the files you want to read with `get_next_line()` inside the cloned directory.

You can retrieve the three text files provided for testing from the previous commit:
```sh
git show HEAD^ pawmot.txt > pawmot.txt
git show HEAD^ rui.txt > rui.txt
git show HEAD^ takano.txt > takano.txt
```
Use the Makefile to compile `get_next_line.c` and `get_next_line_utils.c`. Any one of the following commands can be used:
```sh
make
make all
make get_next_line
```
Run the resulting executable, `get_next_line`:
```sh
./get_next_line
```

To build the bonus version, use the Makefile's `bonus` rule:
```sh
make bonus
```
Run the resulting executable, `get_next_line_bonus`:
```sh
./get_next_line_bonus
```
Compare the output with the contents of the input files to verify the results.

## Resources
Prog.さな雑記 — a notebook of programming information
https://progzakki.sanachan.com/program-lang/c/how-to-use-read/

### Use of AI
None of the program code in this project was written by AI. All code was written by rutakano (intra username). AI was used to set up the debugging environment in VS Code and to translate this README into English.

## Algorithm
When `read()` reads `BUFFER_SIZE` bytes from the specified file, some of the data may remain after a line has been extracted.

For example, if `buff` is the buffer used by `read()` and contains the following data, `"Hello\n"` is treated as one line, leaving `"42Tokyo"` as leftover data:
```c
buff = "Hello\n42Tokyo";
```
This leftover data would normally be lost when the function returns.
To make it available on the next call, `get_next_line()` declares a static linked list using the following structure. The structure is defined in `get_next_line.h` (`get_next_line_bonus.h` for the bonus version).
```c
// Structure definition
typedef struct s_file
{
	char	*surplus;
	int		fd;
	struct s_file	*next;
}	t_file;


char	*get_next_line(int fd)
{
	static t_file	**files;
	/* ... */
}
```
A static linked list is used to meet the bonus requirements by preserving leftover data separately for each file descriptor.
The functions `find_file_node()` and `lst_add_back()` append nodes to the linked list `files`.
Using this list, `ft_get_line()` extracts a line from the specified file.

## Technical Choices

### Specifying BUFFER_SIZE
The value of the `BUFFER_SIZE` macro can be set at compile time with the compiler option `-D BUFFER_SIZE=n`. If this value is zero or negative, or greater than or equal to `SSIZE_MAX`, the maximum number of bytes that `read()` can return, the function immediately returns `NULL`.
Even when the value is within this range, if `read()` fails, the memory allocated for both `buff` and `line` is freed.

### Maximum Line Length
If a line would exceed `SIZE_MAX`, `ft_realloc()` handles the error when attempting to expand `line`.

### Memory Management
The buffer `buff`, allocated for use by `read()`, is freed when `get_next_line()` returns.
The memory for `line`, which stores the extracted line, is not freed by `get_next_line()` when the read succeeds. In the test `main()` function, this memory is freed after the contents of `line` are printed with `printf()`.
The leftover data `surplus` is a member of a node in the static linked list `lists` (of type `t_list **`). It is freed only if `read()` fails.

Static variables are released when `main()` finishes, so no memory leaks occur.
