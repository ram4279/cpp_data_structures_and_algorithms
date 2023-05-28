#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main() {
  // Create the file.
  int fd = open("myfile.txt", O_RDWR | O_CREAT, (mode_t)0600);
  if (fd < 0) {
    perror("open");
    exit(1);
  }

  // Get the file size.
  struct stat statbuf;
  fstat(fd, &statbuf);
  size_t file_size = statbuf.st_size;

  // Map the file into memory.
  void *mapped_file = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (mapped_file == MAP_FAILED) {
    perror("mmap");
    printf("errno = %d\n", errno);
    exit(1);
  }

  // Write to the file.
  char *buffer = mapped_file;
  strcpy(buffer, "Hello, world!");

  // Flush the changes to disk.
  msync(mapped_file, file_size, MS_SYNC);

  // Unmap the file.
  munmap(mapped_file, file_size);

  // Close the file.
  close(fd);

  return 0;
}