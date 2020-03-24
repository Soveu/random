bits 64

section .text
global is_overflow_flag_set

is_overflow_flag_set:
  mov     rax, 0
  mov     rdx, 1
  cmovo   rax, rdx
  ret

