#include <unistd.h>

int main() {
  const char msg[] = "Tracee here!\n";
  write(1, msg, sizeof(msg));
  return 0;
}

