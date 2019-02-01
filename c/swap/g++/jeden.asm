	.file	"main.cpp"
	.intel_syntax noprefix
	.text
	.globl	main
	.type	main, @function
main:
.LFB2006:
	.cfi_startproc
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	sub	rsp, 16
	.cfi_def_cfa_offset 32
	mov	ebx, 40
	mov	rax, QWORD PTR fs:[rbx]
	mov	QWORD PTR 8[rsp], rax
	xor	eax, eax
	mov	DWORD PTR [rsp], 7
	mov	DWORD PTR 4[rsp], 13
	mov	rsi, rsp
	lea	rdi, _ZSt3cin[rip]
	call	_ZNSirsERi@PLT
	lea	rsi, 4[rsp]
	mov	rdi, rax
	call	_ZNSirsERi@PLT
#APP
# 25 "main.cpp" 1
	
#############################################

# 0 "" 2
#NO_APP
	mov	eax, DWORD PTR [rsp]
	mov	edx, DWORD PTR 4[rsp]
	mov	DWORD PTR [rsp], edx
	mov	DWORD PTR 4[rsp], eax
#APP
# 29 "main.cpp" 1
	
#############################################

# 0 "" 2
#NO_APP
	mov	eax, DWORD PTR [rsp]
	mov	edx, DWORD PTR 4[rsp]
	mov	DWORD PTR [rsp], edx
	mov	DWORD PTR 4[rsp], eax
#APP
# 33 "main.cpp" 1
	
#############################################

# 0 "" 2
#NO_APP
	mov	eax, DWORD PTR [rsp]
	mov	edx, DWORD PTR 4[rsp]
	mov	DWORD PTR [rsp], edx
	mov	DWORD PTR 4[rsp], eax
#APP
# 37 "main.cpp" 1
	
#############################################

# 0 "" 2
#NO_APP
	mov	eax, DWORD PTR [rsp]
	mov	edx, DWORD PTR 4[rsp]
	mov	DWORD PTR [rsp], edx
	mov	DWORD PTR 4[rsp], eax
#APP
# 47 "main.cpp" 1
	
#############################################

# 0 "" 2
#NO_APP
	mov	rcx, QWORD PTR 8[rsp]
	xor	rcx, QWORD PTR fs:[rbx]
	jne	.L4
	mov	eax, 0
	add	rsp, 16
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.L4:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2006:
	.size	main, .-main
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2492:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	lea	rdi, _ZStL8__ioinit[rip]
	call	_ZNSt8ios_base4InitC1Ev@PLT
	lea	rdx, __dso_handle[rip]
	lea	rsi, _ZStL8__ioinit[rip]
	mov	rdi, QWORD PTR _ZNSt8ios_base4InitD1Ev@GOTPCREL[rip]
	call	__cxa_atexit@PLT
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2492:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 8.2.1 20180831"
	.section	.note.GNU-stack,"",@progbits
