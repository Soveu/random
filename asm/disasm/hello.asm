bits 64

SYS_exit  equ 60

section .text

global _start
_start:
        call main
        push rax

	mov eax, SYS_exit
        pop rdi
	syscall
main:
        xor rax, rax
        jmp tricky
        db "Sorry, no code here ;)"
tricky:
        inc rax
        ret

