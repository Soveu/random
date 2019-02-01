#include<stdio.h>

#define WIDTH 16
#define SEARCH 0x100

void hexdump(char* from, char* to){
    while(from != to){
        printf("%x: ", from);

        for(int i=WIDTH; i >0; --i){
            printf("%02hhX ", *from);
            ++from;
            if(from == to) break;
        }

        printf("\n");
    }
}

void test(char* y){
    char x[] = "aaaabbbbccccddddeeeeffff";

    printf("%s %s\n%X %X\n\n", x, y, x, y);
    hexdump(x-SEARCH, x+SEARCH);

    return;
}
int main(){
    char x[] = "AAAABBBBCCCCDDDDEEEEFFFF";
    test(x);

    puts("\n\n");
    hexdump(x-SEARCH, x+SEARCH);

    return 0;
}
