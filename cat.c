// Title:  cat
// Name:   cat.c
// Author: Matayoshi
// Date:   2009/05/28 Thu.
// Ver:    1.5.0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void help(void);
void show_ver(void);
void disp(char *filename);
void type_mode(void);

int main(int argc,char *argv[]) {
	int c;

	// オプション解析
	while(( c = getopt(argc, argv, "hv")) != -1) {
		switch (c){
			case 'h':
				// ヘルプ呼び出し
				help();
				break;
			case 'v':
				show_ver();
				break;
/*
			// 「-f」オプションが指定された場合 f:
			case 'f':
				fprintf( stdout, "-fオプション: %s\n", optarg );
				break;
			// それ以外のオプションが指定された場合
*/
			default:
				fprintf( stderr, "usage: %s -hv\n", argv[0] );
				help();
		}
	}

	/* オプション以外の引数に対する処理 */
	while (optind < argc){
		disp(argv[optind++]);
	}

	// 引数がない場合は、デフォルトモード
	if(argc == 1) {
		type_mode();
	}
	return 0;
}

// ファイルを読み込んで表示する
void disp(char *filename) {
//	char buf[1025];
	int i;
	FILE *fp;

	// ファイルオープン
	if ( (fp = fopen(filename, "r")) == NULL) {
		// 読み取り失敗
		fprintf(stderr,"The file was not able to be opened.");
	} else {

		// ファイルから改行単位で読み出して改行を'\0'に書き換えて表示
/*		while ( fscanf(fp,"%s\n",buf) != EOF) {
			buf[strlen(buf)] = '\0';
			printf("%s\n", buf);
		}
/*/
		// 一文字ずつ出力(タブも出力可能)
		while ((i = fgetc(fp)) != EOF) {
			fputc(i, stdout);
		}
/**/
		// ファイルのクローズ
		fclose(fp);
	}
	printf("\n");
	//exit(0);
}

// 標準入力から取得し、そのまま表示する。
void type_mode(void) {
	char buf[513];
	while (1) {
		    // fgetsは取得に失敗した場合NULLを返却する。
		if (fgets(buf, 513, stdin) == NULL) {
			// Ctrl+Cによる終了
			exit(0);
		}

		// 改行文字が含まれているかの確認
		if (strchr(buf, '\n') != NULL) {
			// 改行文字を終端記号に置換する
			buf[strlen(buf) - 1] = '\0';
		} else {
			// 入力ストリームをクリアする
			fflush(stdin);
		}
		printf("%s\n", buf);
	}
}

// バージョン表示
void show_ver(void) {
	printf("Version.1.5.0\n");
	printf("Copyright(C)2009. Matayoshi.\n");
	exit(0);
}

// ヘルプ表示
void help(void) {
	printf("Help\n");
	printf("This command is an imitation of the cat command of linux.\n\n");
	printf("format: [-h] [-v] file\n");
	printf("-h:Help is displayed.\n");
	printf("-v:Version information is displayed.\n");
	printf("-h option and -v option are exclusive.\n");
	exit(0);
}
