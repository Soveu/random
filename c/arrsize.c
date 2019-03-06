#include<string.h>

#define KILO (1000)
#define MEGA (KILO * 1000)

#define N (1000 * MEGA)

/* never? segfaults */
//char tab[N];

int main() {
  /* segfaults at circa 8MB */
//  char tab[N] = {0};

  /* same as global */
  static char tab[N];

  memset(tab, 'A', N);

  return 0;
}

