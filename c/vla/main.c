#include<iostream>

int main(){
  size_t x;

  std::cin >> x;

  int foo[x];

  return sizeof(foo);
}

/* function sym.main () {
    //  3 basic blocks

    loc_0x11c0:

       //DATA XREF from entry0 (+0x21)
       push rbp
       rbp = rsp
       rsp -= 0x40
       rax = qword fs:[0x28]    //[0x28:8]=0x3b40 ; '('
       qword [local_8h] = rax
       dword [local_14h] = 0
       rdi = qword [reloc._ZSt3cin] //[0x3fd8:8]=0
       rsi = qword [local_10h]
       sym.std::istream::operator___unsignedlong ()
       rsi = qword [local_10h]
       rdi = rsp
       qword [local_20h] = rdi
       rdi = qword [rsi*4 + 0xf]
       rdi &= 0xfffffffffffffff0
       rcx = rsp
       rcx -= rdi
       rsp = rcx
       rcx = rsi
       rcx <<<= 2
       qword [local_28h] = rsi
       edx = ecx
       dword [local_14h] = edx
       rcx = qword [local_20h]
       rsp = rcx
       edx = dword [local_14h]
       rcx = qword fs:[0x28]    //[0x28:8]=0x3b40 ; '('
       rsi = qword [local_8h]
       var = rcx - rsi
       qword [local_30h] = rax
       dword [local_34h] = edx
       if (var) goto 0x124b     //unlikely
       {
        loc_0x124b:

           //CODE XREF from sym.main (0x123d)
           void __stack_chk_fail(void)
                                    //sym.imp.__stack_chk_fail ()
        loc_0x1243:

           eax = dword [local_34h]
           rsp = rbp

           return
      }
      return;
  }

-----------------------------------------------------

            ;-- main:
/ (fcn) sym.main 144
|   sym.main (int argc, char **argv, char **envp);
|           ; var int local_34h @ rbp-0x34
|           ; var int local_30h @ rbp-0x30
|           ; var int local_28h @ rbp-0x28
|           ; var int local_20h @ rbp-0x20
|           ; var int local_14h @ rbp-0x14
|           ; var int local_10h @ rbp-0x10
|           ; var int local_8h @ rbp-0x8
|           ; DATA XREF from entry0 (+0x21)
|           0x000011c0      55             push rbp
|           0x000011c1      4889e5         mov rbp, rsp
|           0x000011c4      4883ec40       sub rsp, 0x40
|           0x000011c8      64488b042528.  mov rax, qword fs:[0x28]    ; [0x28:8]=0x3b40 ; '('
|           0x000011d1      488945f8       mov qword [local_8h], rax
|           0x000011d5      c745ec000000.  mov dword [local_14h], 0
|           0x000011dc      488b3df52d00.  mov rdi, qword [reloc._ZSt3cin] ; [0x3fd8:8]=0
|           0x000011e3      488d75f0       lea rsi, qword [local_10h]
|           0x000011e7      e864feffff     call sym.std::istream::operator___unsignedlong
|           0x000011ec      488b75f0       mov rsi, qword [local_10h]
|           0x000011f0      4889e7         mov rdi, rsp
|           0x000011f3      48897de0       mov qword [local_20h], rdi
|           0x000011f7      488d3cb50f00.  lea rdi, qword [rsi*4 + 0xf]
|           0x000011ff      4883e7f0       and rdi, 0xfffffffffffffff0
|           0x00001203      4889e1         mov rcx, rsp
|           0x00001206      4829f9         sub rcx, rdi
|           0x00001209      4889cc         mov rsp, rcx
|           0x0000120c      4889f1         mov rcx, rsi
|           0x0000120f      48c1e102       shl rcx, 2
|           0x00001213      488975d8       mov qword [local_28h], rsi
|           0x00001217      89ca           mov edx, ecx
|           0x00001219      8955ec         mov dword [local_14h], edx
|           0x0000121c      488b4de0       mov rcx, qword [local_20h]
|           0x00001220      4889cc         mov rsp, rcx
|           0x00001223      8b55ec         mov edx, dword [local_14h]
|           0x00001226      64488b0c2528.  mov rcx, qword fs:[0x28]    ; [0x28:8]=0x3b40 ; '('
|           0x0000122f      488b75f8       mov rsi, qword [local_8h]
|           0x00001233      4839f1         cmp rcx, rsi
|           0x00001236      488945d0       mov qword [local_30h], rax
|           0x0000123a      8955cc         mov dword [local_34h], edx
|       ,=< 0x0000123d      0f8508000000   jne 0x124b
|       |   0x00001243      8b45cc         mov eax, dword [local_34h]
|       |   0x00001246      4889ec         mov rsp, rbp
|       |   0x00001249      5d             pop rbp
|       |   0x0000124a      c3             ret
|       |   ; CODE XREF from sym.main (0x123d)
\       `-> 0x0000124b      e8f0fdffff     call sym.imp.__stack_chk_fail ; void __stack_chk_fail(void)

*/
