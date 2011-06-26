// Title:  sleep
// Name:   sleep.c
// Author: Matayoshi
// Date:   2010/06/20
// Ver:    1.0.0

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[]) {
	// 引数チェック
	if(argc < 2) {
		fprintf(stdout, "Usage: %s msec\n", argv[0]);
		exit(1);
	} else {
		char buf[16];
		int wait = 0;

		// 文字列から数値に変換
		sscanf(argv[1], "%15c", buf);
		if(sscanf(buf, "%d", &wait) != 1) {
			fprintf(stdout, "Usage: %s msec\n", argv[0]);
			exit(1);
		}

		// 引数で指定された msec だけ sleep(wait)
		Sleep(wait);
	}
	return 0;
}
