#include<stdlib.h>
#include<string.h>

#define INC 1024
#define KILO (INC)
#define MEGA (INC * KILO)
#define GIGA (INC * MEGA)

#define SIZE (16 * MEGA)

int main() {
  memset(malloc(SIZE), 'A', SIZE);

  return 0;
}

