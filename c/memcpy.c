#include <string.h>

char b1[] = "qoiewjfoiewjfoiewjfpoiew";
char b2[] = "oiqhjr098321jd09213jd091";

int main() {
  return memcpy(b1, b2, sizeof(b1)) == 0;
}

