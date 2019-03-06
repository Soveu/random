#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void hexdump(char* from, char* to, size_t const width){
    while(from != to){
        printf("%x: ", from);

        for(int i=width; i >0; --i){
            printf("%02hhX ", *from);
            ++from;
            if(from == to) break;
        }

        printf("\n");
    }
}

int main(){
#define SIZE 256
    char* m1 = (char*)malloc(0);
    void* al[SIZE];

    for(size_t i=1; i<SIZE; ++i){
      al[i] = malloc(8 * i);
      //memset(al[i], 'z', 16 * i);
    }

    char* m2 = (char*)malloc(0);

    for(size_t i=1; i<SIZE; i+=3){
      free(al[i]);
    }

    memset(malloc(32), 'Z', 32);
    memset(malloc(32), 'Y', 32);
    memset(malloc(32), 'X', 32);

    hexdump(m1-8, m2+8, 8);
    for(size_t i=1; i<SIZE; i++){
      size_t sz = *((size_t*) (al[i] - 8));
      bool flags[3] = { 
        sz & (1 << 0), 
        sz & (1 << 1),
        sz & (1 << 2)
      };
      
      sz &= ~7;

      printf("%p: %04x - %d %d %d\n", al[i], sz, flags[0], flags[1], flags[2]);
    }

    return 0;
}
