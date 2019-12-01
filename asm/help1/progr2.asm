bits 16

;CALLING CONVENTION
;arguments stack (arguments pushed in reverse order) (caller responsible for cleaning up)
;return    ax

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
  mov ax, [bp+6]
  mov si, [bp+4]
  _encode_loop:
    sub si, 1
    mov dx, 0
    div word [bp+8]
    ;ax = ax / base
    ;dx = ax % base
    mov bx, numbers
    add bx, dx
    mov byte cl, [bx]
    mov bx, [bp+2]
    mov byte [bx+si], cl
    cmp si, 0
    jnz _encode_loop
  ret

;decode_base(input_buf, len, base) -> int
decode_base:
  push word 0
  mov si, [bp+4]
  sub si, 1
  xor ax, ax
  _decode_loop:
    push di
    add word di, [bp]
    mov byte bl, [di]
    pop di
    sub bl, '0'
    and bx, 0xFF
    mul word [bp+6]; rdx:rax = rax * rcx
    add ax, bx
    add word [bp], 1
    cmp word [bp], si
    jl  _decode_loop
  xor dx, dx
  ret

main:
  push bp
  mov bp, sp

  ;ax = read(FD_stdin, input_buf, BUFFER_LENGTH)
  push word 10
  push ax
  push word input_buf
  call decode_base
  ;ax = decode_base(input_buf, ax, 10)
  sub sp, 3*2

  push ax
  push word 16
  push word output_buf+5
  push word 10
  call encode_loop; encode_loop(output_buf+5, 16, ax, 10)
  sub sp, 4*2

  push ax
  push word 16
  push word output_buf+5
  push word 2
  call encode_loop; encode_loop(output_buf+5, 16, ax, 2)
  sub sp, 4*2

  push ax
  push word 16
  push word output_buf+5
  push word 8
  call encode_loop; encode_loop(output_buf+5, 16, ax, 8)
  sub sp, 4*2

  push ax
  push word 16
  push word output_buf+5
  push word 16
  call encode_loop; encode_loop(output_buf+5, 16, ax, 16)
  sub sp, 4*2

  ;write(stdout, output_buf, 88)

  leave
  ret

_start:
  call main
  ;TODO: exit program
