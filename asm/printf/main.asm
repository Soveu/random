bits 64

section .text
global main
extern printf

main:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  push  rax
  mov   rax, 0x41424344
  push  rax
  mov   rsi, rsp

  xor   rax, rax
  push  rax
  mov   rax, 0xA7325
  push  rax
  mov   rdi, rsp

  xor   rax, rax
  call printf

  leave
  ret
