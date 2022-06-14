#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>



int main(int argc, char const *argv[]) {
    // コマンドライン引数からファイル名を取得
    if (argc < 2) {
        perror("ERROR: ファイル名を指定してください\n");
        exit(-1);
    }
    const char *filename;
    filename = argv[1];

    // ファイルをオープン
    int fd; // ファイルディスクリプタ
    fd = open(filename, O_RDONLY);

    // 1024byteごと読みこんで, stdoutに出力
    int8_t buf[1024];
    int eol;
    while (1) {
        eol = read(fd, buf, 1024);
        if (eol == 0) {
            break;
        } else if (eol == -1) {
            perror("ERROR: ファイルの読み込みエラー\n");
        }

  