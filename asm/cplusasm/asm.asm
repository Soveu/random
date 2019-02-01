bits 64

section .text
global asmfunc
asmfunc:
  xor rax, rax
  add rax, rdi
  add rax, rsi
  add rax, rdx
  add rax, rcx
  add rax, r8
  add rax, r9
  ret

