bits 64

SYS_exit  equ 60

section .text
extern main

global _start
_start:
        call main
        push rax

	mov eax, SYS_exit
        pop rdi
	syscall

