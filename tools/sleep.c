// Title:  sleep
// Name:   sleep.c
// Author: Matayoshi
// Date:   2010/06/20
// Ver:    1.0.0

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[]) {
	// �����`�F�b�N
	if(argc < 2) {
		fprintf(stdout, "Usage: %s msec\n", argv[0]);
		exit(1);
	} else {
		char buf[16];
		int wait = 0;

		// �����񂩂琔�l�ɕϊ�
		sscanf(argv[1], "%15c", buf);
		if(sscanf(buf, "%d", &wait) != 1) {
			fprintf(stdout, "Usage: %s msec\n", argv[0]);
			exit(1);
		}

		// �����Ŏw�肳�ꂽ msec ���� sleep(wait)
		Sleep(wait);
	}
	return 0;
}
