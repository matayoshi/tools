// Name:        cat2.c
// Author:      Matayoshi
// Version:     2.1.0
// Last Update: 2011/03/09 Wed
/*
History-----------------------
[+] add; [-] remove; [x] bug fix; [=] optimize;

--Ver.2.1.0(2011/03/09 Wed)
a ��؂蕶���̎w��@�\��ǉ�

--Ver.2.0.2(2010/06/18 Fri)
x �w���v���b�Z�[�W���C��
= �ǂݍ��݋@�\������

--Ver.2.0.1(2010/06/17 Thu)
x tab�̒u���@�\�̃o�O���C��
= �t�@�C�����͗p�ƕW�����͗p�̃R�[�h�𓝈�

--Ver.2.0.0(2010/06/16 Wed)
+ �s�ԍ��\���@�\��ǉ�
+ tab�̒u���@�\��ǉ�
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

// �I�v�V�����ݒ�p
struct options {
	int lines;		// �s�ԍ��\������
	int num;		// �^�u���󔒂ɒu�������邩?
	char padding;	// �󔒂��l�߂邩�A0���l�߂邩
	char delimiter;	// ��؂蕶��
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

	// �����̃`�F�b�N
	for(i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-v") == 0) {			// �o�[�W�����\��
			show_ver();
		} else if(strcmp(argv[i], "-h") == 0) {		// �w���v�\��
			help();
		} else if(strcmp(argv[i], "-z") == 0) {		// �󔒂̑����0�g�p
			option.padding = '0';
		} else if(strcmp(argv[i], "-n") == 0) {		// �s�ԍ��\��
			// �����ݒ�
			if(i+1 < argc && sscanf(argv[i+1], "%d", &option.lines) == 1) {
				char buf[BUFFER_MAX_LEN];
				sprintf(buf, "%d", option.lines);// �����͐��l�ł���̂�
				if(strcmp(argv[i+1], buf) == 0) {// ���l�ɕϊ�������A������ɖ߂�
					i++;
					if(option.lines < DIGIT_MIN) {	// �͈͓��ɔ[�߂�
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
		} else if(strcmp(argv[i], "-t") == 0) {		// �󔒂̐���ݒ�
			// �����ݒ�
			if(i+1 < argc && sscanf(argv[i+1], "%d", &option.num) == 1) {
				char buf[BUFFER_MAX_LEN];
				sprintf(buf, "%d", option.num);		// �����͐��l�ł���̂�
				if(strcmp(argv[i+1], buf) == 0) {// ���l�ɕϊ�������A������ɖ߂�
					i++;
					if(option.num < SPACE_MIN) {	// �͈͓��ɔ[�߂�
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
		} else if(strcmp(argv[i], "-d") == 0) {		// ��؂蕶���̎w��
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
	// �I�v�V�������
	while((c = getopt(argc, argv, "hvzn:")) != -1) {
		switch (c) {
			case 'h':
				// �w���v�Ăяo��
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
// �R�����g
			// �u-f�v�I�v�V�������w�肳�ꂽ�ꍇ f:
			case 'f':
				fprintf( stdout, "-f�I�v�V����: %s\n", optarg );
				break;
			// ����ȊO�̃I�v�V�������w�肳�ꂽ�ꍇ
// �����܂�
			default:
				fprintf(stderr, "usage: %s [-h][-v][-n digit][-z] [file..]\n", argv[0]);
				exit(1);
		}
	}
	// -n �I�v�V�����ň������w�肵�Ȃ������B
	if(use_default == 1) {
		optind--;
	}
	// �I�v�V�����ȊO�̈����ɑ΂��鏈��
	while(optind < argc) {
		disp(option, argv[optind++]);
	}
*/
	i -= no_options;
	if(i == argc) {
		// �t�@�C�����w�肳��Ă��Ȃ��ꍇ�́A�W�����͂���ǂݍ���
		disp(option, NULL);
	} else {
		// �t�@�C����ǂݍ���ŕ\��
		while(i < argc) {
			disp(option, argv[i++]);
			if(i < argc) {
				fprintf(stdout, "\n");
			}
		}
	}
	return 0;
}

// �t�@�C����ǂݍ���ŕ\������
void disp(struct options option, char *filename) {
	char buf[BUFFER_MAX_LEN] = "\0";	// �ǂݍ��݃o�b�t�@
//	int i = 0;
	int count   = 0;					// �s�ԍ�
	int newline = 1;					// ���s
	int len     = 0;					// ��
	char format[16] = "\0";				// �s�ԍ��p�t�H�[�}�b�g
	FILE *fp = stdin;					// �t�@�C���|�C���^

	if(option.lines > 0) {
		// �s�ԍ��p�t�H�[�}�b�g�쐬
		sprintf(format, "%%%c%dd%c ", option.padding, option.lines, option.delimiter);
	}

	// �t�@�C�������w�肳��Ă���Ȃ�t�@�C���I�[�v��
	if(filename != NULL && (fp = fopen(filename, "r")) == NULL) {
		// �ǂݎ�莸�s
		fprintf(stderr,"The file was not able to be opened.");
		return;
	} else {
		// buffer�T�C�Y���ǂݏo��
		while(fgets(buf, BUFFER_MAX_LEN, fp) != NULL) {
			// ���s��& -n �Ȃ�s�ԍ���\��
			if(option.lines > 0 && newline == 1) {
				fprintf(stdout, format, ++count);
				newline = 0;
			}
			// ���s�������܂܂�Ă��邩�̊m�F
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
		// �ꕶ�����o��(�^�u���o�͉\)
		while ((i = fgetc(fp)) != EOF) {
			fputc(i, stdout);
		}
*/
		if(filename != NULL) {
			// �t�@�C���̃N���[�Y
			fclose(fp);
			if(len != 0) {
				fprintf(stdout, "\n");
			}
		}
	}
}

int replace_print(int num, int count, char *buf) {
	int i = 0;

	// �ꕶ�����^�u��u�����Ȃ���o��
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

// �o�[�W�����\��
void show_ver(void) {
	fprintf(stdout, "Version.2.1.0\n");
	fprintf(stdout, "Copyright(C)2010-2011. Matayoshi.\n");
	exit(0);
}

// �w���v�\��
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
