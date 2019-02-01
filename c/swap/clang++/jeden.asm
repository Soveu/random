	.text
	.intel_syntax noprefix
	.file	"main.cpp"
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function __cxx_global_var_init
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  # @__cxx_global_var_init
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
.Lfunc_end0:
	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
	.cfi_endproc
                                        # -- End function
	.text
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	push	r14
	.cfi_def_cfa_offset 16
	push	rbx
	.cfi_def_cfa_offset 24
	sub	rsp, 24
	.cfi_def_cfa_offset 48
	.cfi_offset rbx, -24
	.cfi_offset r14, -16
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 16], rax
	mov	dword ptr [rsp + 12], 7
	mov	dword ptr [rsp + 8], 13
	mov	rdi, qword ptr [rip + _ZSt3cin@GOTPCREL]
	lea	r14, [rsp + 12]
	mov	rsi, r14
	call	_ZNSirsERi@PLT
	lea	rbx, [rsp + 8]
	mov	rdi, rax
	mov	rsi, rbx
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
	mov	rdi, r14
	mov	rsi, rbx
	call	_Z4swapIiEvRT_S1_
	#APP

	#############################################

	#NO_APP
	mov	rdi, r14
	mov	rsi, rbx
	call	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	#APP

	#############################################

	#NO_APP
	mov	rdi, r14
	mov	rsi, rbx
	call	_Z6dofuncIZ4mainE3$_0EvT_
	#APP

	#############################################

	#NO_APP
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 16]
	jne	.LBB1_2
# %bb.1:
	xor	eax, eax
	add	rsp, 24
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	r14
	.cfi_def_cfa_offset 8
	ret
.LBB1_2:
	.cfi_def_cfa_offset 48
	call	__stack_chk_fail@PLT
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.section	.text._Z4swapIiEvRT_S1_,"axG",@progbits,_Z4swapIiEvRT_S1_,comdat
	.weak	_Z4swapIiEvRT_S1_       # -- Begin function _Z4swapIiEvRT_S1_
	.p2align	4, 0x90
	.type	_Z4swapIiEvRT_S1_,@function
_Z4swapIiEvRT_S1_:                      # @_Z4swapIiEvRT_S1_
	.cfi_startproc
# %bb.0:
	mov	eax, dword ptr [rdi]
	mov	ecx, dword ptr [rsi]
	mov	dword ptr [rdi], ecx
	mov	dword ptr [rsi], eax
	ret
.Lfunc_end2:
	.size	_Z4swapIiEvRT_S1_, .Lfunc_end2-_Z4swapIiEvRT_S1_
	.cfi_endproc
                                        # -- End function
	.section	.text._ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_,"axG",@progbits,_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_,comdat
	.weak	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_ # -- Begin function _ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.p2align	4, 0x90
	.type	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_,@function
_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_: # @_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.cfi_startproc
# %bb.0:
	push	r14
	.cfi_def_cfa_offset 16
	push	rbx
	.cfi_def_cfa_offset 24
	sub	rsp, 24
	.cfi_def_cfa_offset 48
	.cfi_offset rbx, -24
	.cfi_offset r14, -16
	mov	r14, rsi
	mov	rbx, rdi
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 16], rax
	call	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	mov	eax, dword ptr [rax]
	mov	dword ptr [rsp + 12], eax
	mov	rdi, r14
	call	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	mov	eax, dword ptr [rax]
	mov	dword ptr [rbx], eax
	lea	rdi, [rsp + 12]
	call	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	mov	eax, dword ptr [rax]
	mov	dword ptr [r14], eax
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 16]
	jne	.LBB3_2
# %bb.1:
	add	rsp, 24
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	r14
	.cfi_def_cfa_offset 8
	ret
.LBB3_2:
	.cfi_def_cfa_offset 48
	call	__stack_chk_fail@PLT
.Lfunc_end3:
	.size	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_, .Lfunc_end3-_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.cfi_endproc
                                        # -- End function
	.text
	.p2align	4, 0x90         # -- Begin function _Z6dofuncIZ4mainE3$_0EvT_
	.type	_Z6dofuncIZ4mainE3$_0EvT_,@function
_Z6dofuncIZ4mainE3$_0EvT_:              # @"_Z6dofuncIZ4mainE3$_0EvT_"
	.cfi_startproc
# %bb.0:
	sub	rsp, 24
	.cfi_def_cfa_offset 32
	mov	rax, qword ptr fs:[40]
	mov	qword ptr [rsp + 16], rax
	mov	qword ptr [rsp], rdi
	mov	qword ptr [rsp + 8], rsi
	mov	rdi, rsp
	call	_ZZ4mainENK3$_0clEv
	mov	rax, qword ptr fs:[40]
	cmp	rax, qword ptr [rsp + 16]
	jne	.LBB4_2
# %bb.1:
	add	rsp, 24
	.cfi_def_cfa_offset 8
	ret
.LBB4_2:
	.cfi_def_cfa_offset 32
	call	__stack_chk_fail@PLT
.Lfunc_end4:
	.size	_Z6dofuncIZ4mainE3$_0EvT_, .Lfunc_end4-_Z6dofuncIZ4mainE3$_0EvT_
	.cfi_endproc
                                        # -- End function
	.section	.text._ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,"axG",@progbits,_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,comdat
	.weak	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_ # -- Begin function _ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.p2align	4, 0x90
	.type	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,@function
_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_: # @_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.cfi_startproc
# %bb.0:
	mov	rax, rdi
	ret
.Lfunc_end5:
	.size	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_, .Lfunc_end5-_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.cfi_endproc
                                        # -- End function
	.text
	.p2align	4, 0x90         # -- Begin function _ZZ4mainENK3$_0clEv
	.type	_ZZ4mainENK3$_0clEv,@function
_ZZ4mainENK3$_0clEv:                    # @"_ZZ4mainENK3$_0clEv"
	.cfi_startproc
# %bb.0:
	mov	rax, qword ptr [rdi]
	mov	rcx, qword ptr [rdi + 8]
	mov	edx, dword ptr [rax]
	mov	esi, dword ptr [rcx]
	mov	dword ptr [rax], esi
	mov	dword ptr [rcx], edx
	ret
.Lfunc_end6:
	.size	_ZZ4mainENK3$_0clEv, .Lfunc_end6-_ZZ4mainENK3$_0clEv
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_main.cpp
	.type	_GLOBAL__sub_I_main.cpp,@function
_GLOBAL__sub_I_main.cpp:                # @_GLOBAL__sub_I_main.cpp
	.cfi_startproc
# %bb.0:
	jmp	__cxx_global_var_init   # TAILCALL
.Lfunc_end7:
	.size	_GLOBAL__sub_I_main.cpp, .Lfunc_end7-_GLOBAL__sub_I_main.cpp
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
