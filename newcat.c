#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("argument not enough\n");
		exit(1);
	}

	int fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		printf("file open failed\n");
		exit(1);
	}

	off_t filesize = lseek(fd, 0, SEEK_END);
	if(filesize == -1) {
		perror("long seek to end fail");
		exit(1);
	}

	char buff[filesize];
	if(read(fd, buff, filesize) != 0) {
		printf("read until EOF failed\n");
		exit(1);
	}

	int lineCnt = 1;
	printf("%d ", lineCnt++); 
	for(int i = 0; i < filesize; i++) {
		printf("%c", buff[i]);
		if(buff[i] == '\n') {
			printf("%d ", lineCnt++);
		}
	}
	printf("\n");
}
