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

	// �I�v�V�������
	while(( c = getopt(argc, argv, "hv")) != -1) {
		switch (c){
			case 'h':
				// �w���v�Ăяo��
				help();
				break;
			case 'v':
				show_ver();
				break;
/*
			// �u-f�v�I�v�V�������w�肳�ꂽ�ꍇ f:
			case 'f':
				fprintf( stdout, "-f�I�v�V����: %s\n", optarg );
				break;
			// ����ȊO�̃I�v�V�������w�肳�ꂽ�ꍇ
*/
			default:
				fprintf( stderr, "usage: %s -hv\n", argv[0] );
				help();
		}
	}

	/* �I�v�V�����ȊO�̈����ɑ΂��鏈�� */
	while (optind < argc){
		disp(argv[optind++]);
	}

	// �������Ȃ��ꍇ�́A�f�t�H���g���[�h
	if(argc == 1) {
		type_mode();
	}
	return 0;
}

// �t�@�C����ǂݍ���ŕ\������
void disp(char *filename) {
//	char buf[1025];
	int i;
	FILE *fp;

	// �t�@�C���I�[�v��
	if ( (fp = fopen(filename, "r")) == NULL) {
		// �ǂݎ�莸�s
		fprintf(stderr,"The file was not able to be opened.");
	} else {

		// �t�@�C��������s�P�ʂœǂݏo���ĉ��s��'\0'�ɏ��������ĕ\��
/*		while ( fscanf(fp,"%s\n",buf) != EOF) {
			buf[strlen(buf)] = '\0';
			printf("%s\n", buf);
		}
/*/
		// �ꕶ�����o��(�^�u���o�͉\)
		while ((i = fgetc(fp)) != EOF) {
			fputc(i, stdout);
		}
/**/
		// �t�@�C���̃N���[�Y
		fclose(fp);
	}
	printf("\n");
	//exit(0);
}

// �W�����͂���擾���A���̂܂ܕ\������B
void type_mode(void) {
	char buf[513];
	while (1) {
		    // fgets�͎擾�Ɏ��s�����ꍇNULL��ԋp����B
		if (fgets(buf, 513, stdin) == NULL) {
			// Ctrl+C�ɂ��I��
			exit(0);
		}

		// ���s�������܂܂�Ă��邩�̊m�F
		if (strchr(buf, '\n') != NULL) {
			// ���s�������I�[�L���ɒu������
			buf[strlen(buf) - 1] = '\0';
		} else {
			// ���̓X�g���[�����N���A����
			fflush(stdin);
		}
		printf("%s\n", buf);
	}
}

// �o�[�W�����\��
void show_ver(void) {
	printf("Version.1.5.0\n");
	printf("Copyright(C)2009. Matayoshi.\n");
	exit(0);
}

// �w���v�\��
void help(void) {
	printf("Help\n");
	printf("This command is an imitation of the cat command of linux.\n\n");
	printf("format: [-h] [-v] file\n");
	printf("-h:Help is displayed.\n");
	printf("-v:Version information is displayed.\n");
	printf("-h option and -v option are exclusive.\n");
	exit(0);
}
