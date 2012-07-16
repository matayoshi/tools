// Name:        cat2.c
// Author:      Matayoshi
// Version:     2.1.0
// Last Update: 2011/03/09 Wed
/*
History-----------------------
[+] add; [-] remove; [x] bug fix; [=] optimize;

--Ver.2.1.0(2011/03/09 Wed)
a 区切り文字の指定機能を追加

--Ver.2.0.2(2010/06/18 Fri)
x ヘルプメッセージを修正
= 読み込み機能を改良

--Ver.2.0.1(2010/06/17 Thu)
x tabの置換機能のバグを修正
= ファイル入力用と標準入力用のコードを統一

--Ver.2.0.0(2010/06/16 Wed)
+ 行番号表示機能を追加
+ tabの置換機能を追加
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <unistd.h>

#define DIGIT_MIN 1
#define DIGIT_MAX 10
#define DIGIT_DEFAULT 5
#define SPACE_MIN 1
#define SPACE_MAX 8
#define SPACE_DEFAULT 4
#define BUFFER_MAX_LEN 64

// オプション設定用
struct options {
	int lines;		// 行番号表示桁数
	int num;		// タブを空白に置き換えるか?
	char padding;	// 空白を詰めるか、0を詰めるか
	char delimiter;	// 区切り文字
};

void help(void);
void show_ver(void);
void disp(struct options option, char *filename);
int replace_print(int num, int count, char *buf);

int main(int argc,char *argv[]) {
//	int c = 0;
	int i = 0;
	int no_options = 0;
//	int use_default = 0;
	struct options option = {
		0,
		0,
		' ',
		' '
	};

	// 引数のチェック
	for(i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-v") == 0) {			// バージョン表示
			show_ver();
		} else if(strcmp(argv[i], "-h") == 0) {		// ヘルプ表示
			help();
		} else if(strcmp(argv[i], "-z") == 0) {		// 空白の代わりに0使用
			option.padding = '0';
		} else if(strcmp(argv[i], "-n") == 0) {		// 行番号表示
			// 桁数設定
			if(i+1 < argc && sscanf(argv[i+1], "%d", &option.lines) == 1) {
				char buf[BUFFER_MAX_LEN];
				sprintf(buf, "%d", option.lines);// 引数は数値であるのか
				if(strcmp(argv[i+1], buf) == 0) {// 数値に変換した後、文字列に戻す
					i++;
					if(option.lines < DIGIT_MIN) {	// 範囲内に納める
						option.lines = DIGIT_MIN;
					} else if(option.lines > DIGIT_MAX) {
						option.lines = DIGIT_MAX;
					}
				} else {
					option.lines = DIGIT_DEFAULT;
				}
			} else {
				option.lines = DIGIT_DEFAULT;
			}
		} else if(strcmp(argv[i], "-t") == 0) {		// 空白の数を設定
			// 桁数設定
			if(i+1 < argc && sscanf(argv[i+1], "%d", &option.num) == 1) {
				char buf[BUFFER_MAX_LEN];
				sprintf(buf, "%d", option.num);		// 引数は数値であるのか
				if(strcmp(argv[i+1], buf) == 0) {// 数値に変換した後、文字列に戻す
					i++;
					if(option.num < SPACE_MIN) {	// 範囲内に納める
						option.num = SPACE_MIN;
					} else if(option.num > SPACE_MAX) {
						option.num = SPACE_MAX;
					}
				} else {
					option.num = SPACE_DEFAULT;
				}
			} else {
				option.num = SPACE_DEFAULT;
			}
		} else if(strcmp(argv[i], "-d") == 0) {		// 区切り文字の指定
			if(i < argc) {
				i++;
				option.delimiter = argv[i][0];		// "-d ?"
			} else {
				fprintf(stdout, "delimiter use ' '(space)\n");
			}
		} else if(strncmp(argv[i], "-", 1) == 0) {
			fprintf(stderr, "usage: mycat2 [-h][-v][-n digit][-t num][-d delimiter][-z] [file..]\n");
			exit(1);
		} else {
			no_options++;
		}
	}
/*
	// オプション解析
	while((c = getopt(argc, argv, "hvzn:")) != -1) {
		switch (c) {
			case 'h':
				// ヘルプ呼び出し
				help();
				break;
			case 'v':
				show_ver();
				break;
			case 'n':
				if(sscanf(optarg, "%d", &option.lines) == 1) {
					if(option.lines < DIGIT_MIN) {
						option.lines = DIGIT_MIN;
					} else if(option.lines > DIGIT_MAX) {
						option.lines = DIGIT_MAX;
					}
				} else {
					use_default = 1;
					option.lines = DIGIT_DEFAULT;
				}
				break;
			case 'z':
				option.padding = '0';
				break;
// コメント
			// 「-f」オプションが指定された場合 f:
			case 'f':
				fprintf( stdout, "-fオプション: %s\n", optarg );
				break;
			// それ以外のオプションが指定された場合
// ここまで
			default:
				fprintf(stderr, "usage: %s [-h][-v][-n digit][-z] [file..]\n", argv[0]);
				exit(1);
		}
	}
	// -n オプションで引数を指定しなかった。
	if(use_default == 1) {
		optind--;
	}
	// オプション以外の引数に対する処理
	while(optind < argc) {
		disp(option, argv[optind++]);
	}
*/
	i -= no_options;
	if(i == argc) {
		// ファイルが指定されていない場合は、標準入力から読み込む
		disp(option, NULL);
	} else {
		// ファイルを読み込んで表示
		while(i < argc) {
			disp(option, argv[i++]);
			if(i < argc) {
				fprintf(stdout, "\n");
			}
		}
	}
	return 0;
}

// ファイルを読み込んで表示する
void disp(struct options option, char *filename) {
	char buf[BUFFER_MAX_LEN] = "\0";	// 読み込みバッファ
//	int i = 0;
	int count   = 0;					// 行番号
	int newline = 1;					// 改行
	int len     = 0;					// 桁
	char format[16] = "\0";				// 行番号用フォーマット
	FILE *fp = stdin;					// ファイルポインタ

	if(option.lines > 0) {
		// 行番号用フォーマット作成
		sprintf(format, "%%%c%dd%c ", option.padding, option.lines, option.delimiter);
	}

	// ファイル名が指定されているならファイルオープン
	if(filename != NULL && (fp = fopen(filename, "r")) == NULL) {
		// 読み取り失敗
		fprintf(stderr,"The file was not able to be opened.");
		return;
	} else {
		// bufferサイズ分読み出し
		while(fgets(buf, BUFFER_MAX_LEN, fp) != NULL) {
			// 改行後& -n なら行番号を表示
			if(option.lines > 0 && newline == 1) {
				fprintf(stdout, format, ++count);
				newline = 0;
			}
			// 改行文字が含まれているかの確認
			if(strchr(buf, '\n') != NULL) {
				newline = 1;
			}
			if(option.num > 0) {
				len = replace_print(option.num, len, buf);
			} else {
				fprintf(stdout, "%s", buf);
			}
		}
/*
		// 一文字ずつ出力(タブも出力可能)
		while ((i = fgetc(fp)) != EOF) {
			fputc(i, stdout);
		}
*/
		if(filename != NULL) {
			// ファイルのクローズ
			fclose(fp);
			if(len != 0) {
				fprintf(stdout, "\n");
			}
		}
	}
}

int replace_print(int num, int count, char *buf) {
	int i = 0;

	// 一文字ずつタブを置換しながら出力
	while(*buf != '\0') {
		switch(*buf) {
			case '\t':
				for(i=0; i<num - (count % num); i++) {
					fputc(' ', stdout);
				}
				count += num - (count % num);
				break;
			case '\n':
				count = -1;
			default:
				count++;
				fputc(*buf, stdout);
				break;
		}
		buf++;
	}
	return count;
}

// バージョン表示
void show_ver(void) {
	fprintf(stdout, "Version.2.1.0\n");
	fprintf(stdout, "Copyright(C)2010-2011. Matayoshi.\n");
	exit(0);
}

// ヘルプ表示
void help(void) {
	fprintf(stdout, "Help\n");
	fprintf(stdout, "This command is an imitation of the cat command of linux.\n\n");
	fprintf(stdout, "format: [-h][-v][-n digit(%d-%-d)][-t num(%d-%d)][-z] [file..]\n",
			 DIGIT_MIN, DIGIT_MAX, SPACE_MIN, SPACE_MAX);
	fprintf(stdout, "-h           : Help is displayed.\n");
	fprintf(stdout, "-v           : Version information is displayed.\n");
	fprintf(stdout, "-n digit     : Show line number. digit default is %d.\n",
			 DIGIT_DEFAULT);
	fprintf(stdout, "-t num       : 1 tab = num spaces. num default is %d.\n",
			 SPACE_DEFAULT);
	fprintf(stdout, "-d delimiter : The line number and text delimiter. default is ' '(space).\n");
	fprintf(stdout, "-z           : Line number padding. 0 is used instead of the space.\n");
	fprintf(stdout, "-h option and -v option are exclusive.\n");
	exit(0);
}
