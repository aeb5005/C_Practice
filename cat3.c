// no error handling, for brevity
// you can copy between file descriptors without allocating any memory using sendfile(2)) on Linux (2.6.33 or newer)

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int i;
  
  for(i = 1; 1 != argc; i++) {
  int fd;
  struct stat stats;
  
  fd = open(argv[i], O_RDONLY);
  fstat(fd, &stats);
  sendfile(STDOUT_FILENO, fd, NULL, stats.st_size);
  }
}
