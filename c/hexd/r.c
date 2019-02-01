#include<stdio.h>

char *id(char *v)
{ 
    return v; 
} 

char* f(char a){
    char stos[4096] = {a,};
    char lazagna[] = "aaaabbbbccccdddd\0";
    return id(lazagna); 
} 

int main()
{ 
    printf("%s\n", f('a')); 
}
