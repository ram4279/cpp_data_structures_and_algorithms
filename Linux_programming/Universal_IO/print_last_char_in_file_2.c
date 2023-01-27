#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if (argc != 2) {
		printf("eg: %s file.txt\n", argv[0]);
		return -1;
	}

	char buffer[8] = {0};
	
	int file_r = open(argv[1], O_RDONLY);
	lseek(file_r, 0, SEEK_END);
	lseek(file_r, -3, SEEK_CUR);
	
	read(file_r, buffer, 8);
	printf("buffer = %s", buffer);

	close(file_r);
}
