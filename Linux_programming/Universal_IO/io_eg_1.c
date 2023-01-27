#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc,  char** argv)
{
	if (argc != 3) {
		printf("eg %s file1.txt file2.txt\n", argv[0]);
		return -1;
	}

	int file_rd = open(argv[1], O_RDONLY);
	if (file_rd == -1) {
		perror("File open error\n");
		exit(1);
	}

	int open_flags = O_CREAT | O_WRONLY | O_TRUNC;
	int file_permission = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw- */
	int file_wt = open(argv[2], open_flags, file_permission);
	if (file_wt == -1) {
		perror("File open error\n");
		exit(1);
	}

	ssize_t numRead;
	char buf[BUF_SIZE];

	while ((numRead = read(file_rd, buf, sizeof(buf))) > 0) {
		if (write(file_wt, buf, numRead) != numRead) {
			perror("Write error");
			exit(1);
		}
	}

	close(file_rd);
	close(file_wt);
	return 0;
}
