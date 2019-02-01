	.text
	.intel_syntax noprefix
	.file	"main.cpp"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 16], rax
	mov	dword ptr [rsp + 12], 7
	mov	dword ptr [rsp + 8], 13
	mov	rdi, qword ptr [rip + _ZSt3cin@GOTPCREL]
	lea	rsi, [rsp + 12]
	call	_ZNSirsERi@PLT
	lea	rsi, [rsp + 8]
	mov	rdi, rax
	call	_ZNSirsERi@PLT
	#APP

	#############################################

	#NO_APP
	mov	eax, dword ptr [rsp + 12]
	mov	ecx, dword ptr [rsp + 8]
	mov	dword ptr [rsp + 12], ecx
	mov	dword ptr [rsp + 8], eax
	#APP

	#############################################

	#NO_APP
	mov	eax, dword ptr [rsp + 12]
	mov	ecx, dword ptr [rsp + 8]
	mov	dword ptr [rsp + 12], ecx
	mov	dword ptr [rsp + 8], eax
	#APP

	#############################################

	#NO_APP
	mov	eax, dword ptr [rsp + 12]
	mov	ecx, dword ptr [rsp + 8]
	mov	dword ptr [rsp + 12], ecx
	mov	dword ptr [rsp + 8], eax
	#APP

	#############################################

	#NO_APP
	mov	eax, dword ptr [rsp + 12]
	mov	ecx, dword ptr [rsp + 8]
	mov	dword ptr [rsp + 12], ecx
	mov	dword ptr [rsp + 8], eax
	#APP

	#############################################

	#NO_APP
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 16]
	jne	.LBB0_2
# %bb.1:
	xor	eax, eax
	add	rsp, 24
	.cfi_def_cfa_offset 8
	ret
.LBB0_2:
	.cfi_def_cfa_offset 32
	call	__stack_chk_fail@PLT
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_main.cpp
	.type	_GLOBAL__sub_I_main.cpp,@function
_GLOBAL__sub_I_main.cpp:                # @_GLOBAL__sub_I_main.cpp
	.cfi_startproc
# %bb.0:
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset rbx, -16
	lea	rbx, [rip + _ZStL8__ioinit]
	mov	rdi, rbx
	call	_ZNSt8ios_base4InitC1Ev@PLT
	mov	rdi, qword ptr [rip + _ZNSt8ios_base4InitD1Ev@GOTPCREL]
	lea	rdx, [rip + __dso_handle]
	mov	rsi, rbx
	pop	rbx
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit@PLT        # TAILCALL
.Lfunc_end1:
	.size	_GLOBAL__sub_I_main.cpp, .Lfunc_end1-_GLOBAL__sub_I_main.cpp
	.cfi_endproc
                                        # -- End function
	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_main.cpp

	.ident	"clang version 7.0.0 (tags/RELEASE_700/final)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym _GLOBAL__sub_I_main.cpp
	.addrsig_sym __stack_chk_fail
	.addrsig_sym _ZStL8__ioinit
	.addrsig_sym __dso_handle
	.addrsig_sym _ZSt3cin
