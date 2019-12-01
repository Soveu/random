bits 64

;CALLING CONVENTION
;arguments rdi rsi rdx r10 r9 r8
;return    rax

;declaring constants
SYS_exit  equ 60
SYS_read  equ 0
SYS_write equ 1

FD_stdin  equ 0
FD_stdout equ 1
FD_stderr equ 2

BUFFER_LENGTH equ 20

section .bss
  input_buf   resb BUFFER_LENGTH; char buf[BUFFER_LENGTH]

section .rodata
  numbers     db "0123456789ABCDEF"

section .data
  output_buf  db "dec: 0000000000000000", 10, "oct: 0000000000000000", 10, "bin: 0000000000000000", 10, "hex: 0000000000000000", 10, 0

section .text

;encode_loop(output_buf, len, int, base)
encode_loop:
  mov rax, rdx
  push rsi; save value of rsi for later
  _zero_loop:
    sub rsi, 1
    mov byte [rdi+rsi], '0'
    cmp rsi, 0
    jnz _zero_loop
  pop rsi; restore saved value
  _encode_loop:
    sub rsi, 1
    mov rdx, 0
    div r10
    ;rax = rax / r10
    ;rdx = rax % r10
    mov cl, [numbers+rdx]
    mov byte [rdi+rsi], cl
    cmp rsi, 0
    jnz _encode_loop
  ret

;decode_base(input_buf, len, base) -> int
decode_base:
  mov r15, 0
  sub rsi, 1
  xor rax, rax
  mov rcx, rdx;rax and rdx must be free to allow multiplication
  _decode_loop:
    mov bl, [rdi+r15]
    sub bl, '0'
    and rbx, 0xFF
    mul rcx; rdx:rax = rax * rcx
    add rax, rbx
    add r15, 1
    cmp r15, rsi
    jl  _decode_loop
  xor rdx, rdx
  ret

main:
  push rbp
  mov rbp, rsp

  mov rax, SYS_read
  mov rdi, FD_stdin
  mov rsi, input_buf
  mov rdx, BUFFER_LENGTH
  syscall; read data from input
  ;rax = read(FD_stdin, input_buf, BUFFER_LENGTH)

  lea rdi, [input_buf]
  mov rsi, rax
  mov rdx, 10
  call decode_base
  ;rax = decode_base(input_buf, rax, 10)
  mov r14, rax

  mov r10, 10
  mov rdx, r14
  mov rsi, 16
  lea rdi, [output_buf+5]
  call encode_loop; encode_loop(output_buf, 64, r14)

  mov r10, 8
  mov rdx, r14
  mov rsi, 16
  lea rdi, [output_buf+27]
  call encode_loop; encode_loop(output_buf, 64, r14)

  mov r10, 2
  mov rdx, r14
  mov rsi, 16
  lea rdi, [output_buf+49]
  call encode_loop; encode_loop(output_buf, 64, r14)

  mov r10, 16
  mov rdx, r14
  mov rsi, 16
  lea rdi, [output_buf+71]
  call encode_loop; encode_loop(output_buf, 64, r14)

  mov rax, SYS_write
  mov rdi, FD_stdout
  lea rsi, [output_buf]
  mov rdx, 88
  syscall

  leave
  ret

global _start
_start:
  call main
  mov rdi, rax
  mov rax, SYS_exit
  syscall; exit(main())

