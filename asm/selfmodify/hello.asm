bits 64

global _start

section .text
_start:
  mov byte [nops+8], 0xCC
nops:
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop

  mov rax, 1
  mov rdi, 1
  mov rsi, msg
  mov rdx, 13
  syscall
  
  mov eax, 60
  xor rdi, rdi
  syscall

msg:
	db "Hello world", 10, 0
