// cat: credit 2014 robert clausecker <fuz@fuz.su>
// todo: choose buffer size dynamically

#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "err.h"

extern int    main(int, char*[]);
static void   output_file(const char*);

// implementation according to IEEE std 1003.1, 2013 edition

extern int
main(int argc, char *argv[])
{
  int optchar;
  int i;
  
  setprogname(argv[0]);
  
  while ((optchar = getopt(argc, argv, "u")) != -1)
    switch (optchar) {
    case 'u':
      // buffering behaves like -u by default
      break;
    case '?':
      return (2);
    }
  if (optind == argc) {
    output_file("-");
    return (0);
  }
  
  for (i = optind; i < argc; i++) {
    output_file(argv[i]);
  }
  
  return (0);
}

// Copy the contents of the file filename to stdout. stdin is copied to stdout
// of filename is "-". If an error occurs, this function prints a diagnostic to 
// stderr and returns 1. 0 is returned on success. 
static void
output_file(const char *filename)
{
  static char iobuf[BUFSIZ];
  int fd;
  ssize_t read_count, write_count;
  
  if (strcmp(filename, "-") == 0) {
    fd = STDIN_FILENO;
  } else {
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
      // LOCALIZE
      err(1, "Cannot open file %s", filename);
    }
  }
  
  while ((read_count = read(fd, iobuf, sizeof(iobuf))) > 0) {
    write_count = write(STDOUT_FILENO, iobuf, read_count);
    if (write_count < read_count) {
      // LOCALIZE
      err(1, "Error writing to stdout");
    }
  }
  
  if (read_count < 0) {
    // LOCALIZE
    err(1, "Error reading file %s", filename);
  }
  
  if (fd != STDIN_FILENO && close(fd) != 0) {
    // LOCALIZE
    err(1, "Error closing file %s", filename);
  }
}
    
