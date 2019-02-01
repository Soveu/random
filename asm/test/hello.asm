bits 64

global _start

section .text
_start:
	mov eax, 60
	xor rdi, rdi
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, msg
	mov rdx, 13
	syscall

msg:
	db "Hello world", 10
