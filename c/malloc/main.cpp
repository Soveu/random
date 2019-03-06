#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * dump3.txt - allocation loop
 * dump4.txt - allocation loop with free on every 4th element
 */
void hexdump(char* from, char* to, const size_t width=8){
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

#define SIZE 64

int main(){
    char* m1 = (char*)malloc(0) - 8;

    for(size_t i=0; i<SIZE; ++i){
      void* m = malloc(i);
      memset(m, 'z', i);
      if(i % 4 == 0) free(m);
    }

    char* m2 = (char*)malloc(0);
    hexdump(m1, m2);

    return 0;
}
