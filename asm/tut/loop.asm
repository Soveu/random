loop1:
  mov   rcx, qword [lpCnt]
  mov   rax, 1
sumLoop:
  add   qword [sum], rax
  add   rax, 2
  dec   rcx
  cmp   rcx, 0
  jne   sumLoop

loop2:
  mov   rcx, qword [lpCnt]
  mov   rax, 1
sumLoop2:
  add   qword [sum], rax
  add   rax, 2
  loop  sumLoop2
