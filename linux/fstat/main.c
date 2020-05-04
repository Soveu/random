#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>

const char DEBUGSTR[] = "dev_t     %d;\t/* ID of device containing file */\n"
                        "mode_t    %o;\t/* File type and mode */\n"
                        "dev_t     %d;\t/* Device ID (if special file) */\n"
                        "off_t     %d;\t/* Total size, in bytes */\n";
                           
int main() {
  struct stat s;
  fstat(0, &s);
  perror("fstat");
  printf(DEBUGSTR, s.st_dev, s.st_mode, s.st_rdev, s.st_size);
}
