bits 64

; declaring constants
SYS_exit  equ 60
SYS_read  equ 0
SYS_write equ 1

FD_STDIN  equ 0
FD_STDOUT equ 1
FD_STDERR equ 2

BUFLEN    equ 1024

section .data
msg:
	db "Hello wórld", 10, 0
dataend:

; declaring zero-initialized data
section .bss
        buf resb BUFLEN ; char buf[BUFLEN]

section .text
global main
main:
        push rbp
        mov rbp, rsp  ; move stack frame

        mov rax, SYS_read
        mov rdi, FD_STDIN
        mov rsi, buf
        mov rdx, BUFLEN
        syscall       ; read(0, buf, 32)

        mov rdx, rax
        mov rax, SYS_write
        mov rdi, FD_STDOUT
        mov rsi, buf
        syscall       ; write(1, buf, read(0, buf, 32))

	mov rax, SYS_write
	mov rdi, FD_STDOUT
	mov rsi, msg
	mov rdx, dataend-msg
	syscall       ; write(1, "Hello World\n", 13)

        mov rax, 0    ; returning from main with 0
        leave
        ret

