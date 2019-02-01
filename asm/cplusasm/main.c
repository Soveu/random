#include<stdint.h>
#include<stdio.h>

extern uint64_t asmfunc(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t func(
    uint64_t a,
    uint64_t b,
    uint64_t c,
    uint64_t d,
    uint64_t e,
    uint64_t f,
    uint64_t g,
    uint64_t h,
    uint64_t i,
    uint64_t j,
    uint64_t k,
    uint64_t l,
    uint64_t m,
    uint64_t n,
    uint64_t o,
    uint64_t p)
{
  return a + b + c + d + e + f + g + h + i + j + k + l + m + n + o +p;
}

int main(){
  uint64_t x = asmfunc(1,2,3,4,5,6);

  return (int)x;
}

