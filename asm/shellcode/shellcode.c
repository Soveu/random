#include<stdio.h>
#include<stdint.h>

char code[] = "\xb8\x3c\0\0\0\x48\x31\xff\x0f\x05\0";

int main(){
    #include<sys/mman.h>

    uintptr_t pagesize = sysconf(_SC_PAGE_SIZE);
    #define PAGE_START(P) ((uintptr_t)(P) & ~(pagesize-1))
    #define PAGE_END(P)   (((uintptr_t)(P) + pagesize - 1) & ~(pagesize-1))
    mprotect((void *)PAGE_START(code), sizeof(code), PROT_READ|PROT_WRITE|PROT_EXEC);

    void(*func)(void) = (void*) code;
    printf("Executing shellcode\n");
    func();
    printf("Done\n");

    return 0;
}
