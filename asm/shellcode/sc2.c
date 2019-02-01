#include<stdio.h>
#include<stdint.h>

void func(void) = "\xb8\x3c\0\0\0\x48\x31\xff\x0f\x05\0";

int main(){
    printf("Executing shellcode\n");
    func();
    printf("Done\n");

    return 0;
}
