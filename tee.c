// Title:  tee
// Name:   tee.c
// Author: Matayoshi
// Date:   2009/07/09 Thu.
// Ver:    1.1.0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void help(void);
void show_ver(void);
void tee(char *filename,int flag);

int main(int argc,char *argv[]) {
	int c;
	int flag = 0;

	// オプション解析
	while(( c = getopt(argc, argv, "ahv")) != -1) {
		switch (c){
			case 'h':
				// ヘルプ表示
				help();
				break;
			case 'a':
				// 追記フラグ
				flag = 1;
				break;
			case 'v':
				show_ver();
				break;
			default:
				fprintf( stderr, "usage: %s -ha\n", argv[0] );
				help();
		}
	}

	// オプション以外の引数に対する処理 //
	if (optind < argc) {
		tee(argv[optind],flag);
	} else {
		// ファイル名を指定されなかった
		tee(NULL,flag);
	}
	return 0;
}

// 標準出力とファイルに出力
void tee(char *filename,int flag) {
	int i;
	FILE *fp = NULL;
	char *openType = "w";

	if(flag == 1) {
		// 追記モード
		openType = "a";
	}

	// ファイルオープン
	if (filename != NULL) {
		fp = fopen(filename, openType);
	}

	// 一文字ずつ出力(タブも出力可能)
	while ((i = fgetc(stdin)) != EOF) {
		// 標準出力
		fputc(i, stdout);
		if(fp != NULL) {
			// ファイルへ出力
			fputc(i, fp);
		}
	}
	if(fp != NULL) {
		// ファイルのクローズ
		fclose(fp);
	}
}

// バージョン表示
void show_ver(void) {
	printf("Version.1.1.0\n");
	printf("Copyright(C)2009. Matayoshi.\n");
	exit(0);
}

// ヘルプ表示
void help(void) {
	printf("Help\n");
	printf("This command is an imitation of the tee command of linux.\n\n");
	printf("format: [-a] [-h] [-v] file\n");
	printf("-a:A standard input is added to the file without overwriting the content of the file.\n");
	printf("-h:Help is displayed.\n");
	printf("-v:Version information is displayed.\n");
	printf("-h option and -v option are exclusive.\n");
	exit(0);
}
/* vim: set tabstop=4 fileformat=dos : */
// EOF